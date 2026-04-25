// UnrealMeasurementTool - Measurement Actor

#include "MeasurementActor.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"
#include "MeasurementCalculator.h"
#include "MeasurementLabelComponent.h"
#include "MeasurementSnapComponent.h"
#include "MeasurementTxtWgtCommunicationInterface.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

AMeasurementActor::AMeasurementActor()
{
    PrimaryActorTick.bCanEverTick = false;

    SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    SetRootComponent(SplineComponent);

    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
    WidgetComponent->SetupAttachment(SplineComponent);
    WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
    WidgetComponent->SetDrawAtDesiredSize(true);

    SnapComponent = CreateDefaultSubobject<UMeasurementSnapComponent>(TEXT("SnapComponent"));
    LabelComponent = CreateDefaultSubobject<UMeasurementLabelComponent>(TEXT("LabelComponent"));

#if WITH_EDITOR
    SnapComponent->OnPropertiesChanged.AddUObject(this, &AMeasurementActor::OnSnapPropertiesChanged);
    LabelComponent->OnPropertiesChanged.AddUObject(this, &AMeasurementActor::OnLabelPropertiesChanged);
#endif
}

void AMeasurementActor::OnConstruction(const FTransform &Transform)
{
    Super::OnConstruction(Transform);

    if (!bIsProcessingSnap)
    {
        bSnapDirty = true;
        bDebugDrawDirty = true;
    }

    ApplySplinePointType();

#if WITH_EDITOR
    BindEditorCameraDelegate();
#endif

    ScheduleDeferredUpdate();
}

void AMeasurementActor::Destroyed()
{
#if WITH_EDITOR
    UnbindEditorCameraDelegate();
#endif

    GetWorldTimerManager().ClearTimer(DeferredUpdateTimerHandle);
    FlushDebugDraws();
    Super::Destroyed();
}

#if WITH_EDITOR
void AMeasurementActor::BindEditorCameraDelegate()
{
    if (!CameraMovedDelegateHandle.IsValid())
    {
        CameraMovedDelegateHandle = FEditorDelegates::OnEditorCameraMoved.AddWeakLambda(
            this,
            [this](const FVector &Location, const FRotator &, ELevelViewportType, int32)
            {
                OnCameraLocationChanged(Location);
            });
    }
}

void AMeasurementActor::UnbindEditorCameraDelegate()
{
    if (CameraMovedDelegateHandle.IsValid())
    {
        FEditorDelegates::OnEditorCameraMoved.Remove(CameraMovedDelegateHandle);
        CameraMovedDelegateHandle.Reset();
    }
}

void AMeasurementActor::OnCameraLocationChanged(const FVector &CameraLocation)
{
    UpdateBillboard(CameraLocation);
    RefreshDebugDrawIfNeeded();
}
#endif

void AMeasurementActor::ScheduleDeferredUpdate()
{
    if (!GetWorldTimerManager().IsTimerActive(DeferredUpdateTimerHandle))
    {
        GetWorldTimerManager().SetTimer(
            DeferredUpdateTimerHandle, this,
            &AMeasurementActor::ProcessDeferredUpdate,
            KINDA_SMALL_NUMBER, false);
    }
}

void AMeasurementActor::UpdateBillboard(const FVector &CameraLocation)
{
    UMeasurementCalculator::FaceComponentToCamera(WidgetComponent, CameraLocation);
    LabelComponent->FaceLabelsToCamera(CameraLocation);

    constexpr float ReferenceDistance = 500.0f;
    const float WidgetDist = FVector::Dist(WidgetComponent->GetComponentLocation(), CameraLocation);
    const float WidgetScale = FMath::Clamp(WidgetDist / ReferenceDistance, 0.01f, 100.0f);
    WidgetComponent->SetRelativeScale3D(FVector(WidgetScale));
}

void AMeasurementActor::RefreshDebugDrawIfNeeded()
{
    const bool bHiddenNow = IsTemporarilyHiddenInEditor();
    if (bHiddenNow && !bWasHiddenLastFrame)
    {
        FlushDebugDraws();
    }
    bWasHiddenLastFrame = bHiddenNow;

    if (!bHiddenNow && bDebugDrawDirty)
    {
        bDebugDrawDirty = false;
        FlushDebugDraws();
        SnapComponent->DrawDebugVisualization(SplineComponent);
        DrawClosingLine();
        LabelComponent->DrawAngleArcs(SplineComponent, MeasurementMode);
    }
}

void AMeasurementActor::ProcessDeferredUpdate()
{
    ProcessDeferredSnap();

    FVector CameraLocation;
    if (UMeasurementCalculator::GetActiveCameraLocation(GetWorld(), CameraLocation))
    {
        UpdateBillboard(CameraLocation);
    }

    RefreshDebugDrawIfNeeded();
}

void AMeasurementActor::ProcessDeferredSnap()
{
    if (!bSnapDirty)
    {
        return;
    }

    bSnapDirty = false;
    bIsProcessingSnap = true;

    SnapComponent->SnapPoints(SplineComponent);
    RefreshMeasurement();

    bIsProcessingSnap = false;
}

#if WITH_EDITOR
void AMeasurementActor::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    bDebugDrawDirty = true;
    const FName PropName = PropertyChangedEvent.GetPropertyName();

    if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, DisplayUnit))
    {
        RefreshMeasurement();
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, bLinearSpline))
    {
        ApplySplinePointType();
        RefreshMeasurement();
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, MeasurementMode))
    {
        RefreshMeasurement();
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, MainLabelFontSize))
    {
        UpdateMeasurementText();
    }

    ScheduleDeferredUpdate();
}

void AMeasurementActor::OnLabelPropertiesChanged()
{
    bDebugDrawDirty = true;
    RefreshMeasurement();
    ScheduleDeferredUpdate();
}

void AMeasurementActor::OnSnapPropertiesChanged()
{
    bDebugDrawDirty = true;
    SnapComponent->SnapPoints(SplineComponent);
    RefreshMeasurement();
    ScheduleDeferredUpdate();
}
#endif

void AMeasurementActor::ResetSpline()
{
    if (!SplineComponent)
    {
        return;
    }

    bDebugDrawDirty = true;

    // Reset actor rotation and scale, keep location
    SetActorRotation(FRotator::ZeroRotator);
    SetActorScale3D(FVector::OneVector);

    // Reset spline to default 2-point configuration
    SplineComponent->ClearSplinePoints(false);
    SplineComponent->AddSplinePoint(FVector(0.f, 0.f, 0.f), ESplineCoordinateSpace::Local, false);
    SplineComponent->AddSplinePoint(FVector(100.f, 0.f, 0.f), ESplineCoordinateSpace::Local, true);

    ApplySplinePointType();
    RefreshMeasurement();
}

void AMeasurementActor::ApplySplinePointType()
{
    if (!SplineComponent)
    {
        return;
    }

    const ESplinePointType::Type PointType = bLinearSpline ? ESplinePointType::Linear : ESplinePointType::Curve;
    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();

    for (int32 i = 0; i < NumPoints; ++i)
    {
        SplineComponent->SetSplinePointType(i, PointType, false);
    }

    SplineComponent->UpdateSpline();
}

void AMeasurementActor::RefreshMeasurement()
{
    LabelComponent->UpdateLabels(SplineComponent, MeasurementMode, DisplayUnit);
    UpdateMeasurementText();
}

void AMeasurementActor::UpdateMeasurementText()
{
    if (!SplineComponent || !WidgetComponent)
    {
        return;
    }

    UUserWidget *Widget = WidgetComponent->GetWidget();
    if (!Widget)
    {
        return;
    }

    if (!Widget->Implements<UMeasurementTxtWgtCommunicationInterface>())
    {
        return;
    }

    FText FormattedText;

    if (MeasurementMode == EMeasurementMode::Area)
    {
        const TArray<FVector> Points = GetSplineWorldPoints();
        const float AreaCmSq = UMeasurementCalculator::CalculatePolygonArea(Points);
        FormattedText = UMeasurementCalculator::FormatArea(AreaCmSq, DisplayUnit);
    }
    else
    {
        const float SplineLengthCm = SplineComponent->GetSplineLength();
        FormattedText = UMeasurementCalculator::FormatDistance(SplineLengthCm, DisplayUnit);
    }

    IMeasurementTxtWgtCommunicationInterface::Execute_SendMeasurementText(Widget, FormattedText);
    IMeasurementTxtWgtCommunicationInterface::Execute_SendMeasurementFontSize(Widget, MainLabelFontSize);
}

void AMeasurementActor::DrawClosingLine() const
{
    if (MeasurementMode != EMeasurementMode::Area || !bShowClosingLine || !SplineComponent)
    {
        return;
    }

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    if (NumPoints < 3)
    {
        return;
    }

    UWorld *World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector FirstPoint = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
    const FVector LastPoint = SplineComponent->GetLocationAtSplinePoint(NumPoints - 1, ESplineCoordinateSpace::World);

    DrawDebugLine(World, LastPoint, FirstPoint, FColor::Yellow, true, -1.0f, SDPG_World, 2.0f);
}

TArray<FVector> AMeasurementActor::GetSplineWorldPoints() const
{
    TArray<FVector> Points;
    if (!SplineComponent)
    {
        return Points;
    }

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    Points.SetNum(NumPoints);
    for (int32 i = 0; i < NumPoints; ++i)
    {
        Points[i] = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
    }

    return Points;
}

void AMeasurementActor::FlushDebugDraws() const
{
    UWorld *World = GetWorld();
    if (World)
    {
        FlushPersistentDebugLines(World);
    }
}
