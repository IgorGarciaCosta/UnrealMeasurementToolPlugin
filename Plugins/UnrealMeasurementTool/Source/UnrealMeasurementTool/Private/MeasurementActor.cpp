// UnrealMeasurementTool - Measurement Actor

#include "MeasurementActor.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"
#include "MeasurementCalculator.h"
#include "MeasurementLabelComponent.h"
#include "MeasurementSnapComponent.h"
#include "MeasurementTxtWgtCommunicationInterface.h"

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
    }

    ApplySplinePointType();
    UpdateMeasurementText();
    EnsureBillboardTimer();
}

void AMeasurementActor::Destroyed()
{
    GetWorldTimerManager().ClearTimer(BillboardTimerHandle);
    Super::Destroyed();
}

void AMeasurementActor::EnsureBillboardTimer()
{
    if (!GetWorldTimerManager().IsTimerActive(BillboardTimerHandle))
    {
        GetWorldTimerManager().SetTimer(BillboardTimerHandle, this, &AMeasurementActor::UpdateBillboard, 0.1f, true);
    }
}

void AMeasurementActor::UpdateBillboard()
{
    ProcessDeferredSnap();

    FVector CameraLocation;
    if (UMeasurementCalculator::GetActiveCameraLocation(GetWorld(), CameraLocation))
    {
        UMeasurementCalculator::FaceComponentToCamera(WidgetComponent, CameraLocation);
        LabelComponent->FaceLabelsToCamera(CameraLocation);
    }

    if (!IsTemporarilyHiddenInEditor())
    {
        SnapComponent->DrawDebugVisualization(SplineComponent);
        DrawClosingLine();
    }
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
    LabelComponent->UpdateLabels(SplineComponent, MeasurementMode, DisplayUnit);
    UpdateMeasurementText();

    bIsProcessingSnap = false;
}

#if WITH_EDITOR
void AMeasurementActor::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    const FName PropName = PropertyChangedEvent.GetPropertyName();

    if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, ManualSize))
    {
        ApplyManualSize();
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, DisplayUnit))
    {
        UpdateMeasurementText();
        LabelComponent->UpdateLabels(SplineComponent, MeasurementMode, DisplayUnit);
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, bLinearSpline))
    {
        ApplySplinePointType();
        UpdateMeasurementText();
        LabelComponent->UpdateLabels(SplineComponent, MeasurementMode, DisplayUnit);
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, MeasurementMode))
    {
        UpdateMeasurementText();
        LabelComponent->UpdateLabels(SplineComponent, MeasurementMode, DisplayUnit);
    }
}

void AMeasurementActor::OnLabelPropertiesChanged()
{
    LabelComponent->UpdateLabels(SplineComponent, MeasurementMode, DisplayUnit);
    UpdateMeasurementText();
}

void AMeasurementActor::OnSnapPropertiesChanged()
{
    SnapComponent->SnapPoints(SplineComponent);
    UpdateMeasurementText();
}
#endif

void AMeasurementActor::ResetSpline()
{
    if (!SplineComponent)
    {
        return;
    }

    // Reset actor rotation and scale, keep location
    SetActorRotation(FRotator::ZeroRotator);
    SetActorScale3D(FVector::OneVector);

    // Reset spline to default 2-point configuration
    SplineComponent->ClearSplinePoints(false);
    SplineComponent->AddSplinePoint(FVector(0.f, 0.f, 0.f), ESplineCoordinateSpace::Local, false);
    SplineComponent->AddSplinePoint(FVector(100.f, 0.f, 0.f), ESplineCoordinateSpace::Local, true);

    ApplySplinePointType();
    UpdateMeasurementText();
    LabelComponent->UpdateLabels(SplineComponent, MeasurementMode, DisplayUnit);
}

void AMeasurementActor::ApplyManualSize()
{
    if (!SplineComponent)
    {
        return;
    }

    float ScaleFactor = 1.0f;

    // In Area mode, ManualSize is a target area — convert to cm² and use sqrt scaling.
    if (MeasurementMode == EMeasurementMode::Area)
    {
        const float DesiredAreaCmSq = MeasurementUnitUtils::UnitSqToCmSq(ManualSize, DisplayUnit);

        const TArray<FVector> Points = GetSplineWorldPoints();
        const float CurrentArea = UMeasurementCalculator::CalculatePolygonArea(Points);
        if (CurrentArea <= KINDA_SMALL_NUMBER)
        {
            return;
        }

        ScaleFactor = FMath::Sqrt(DesiredAreaCmSq / CurrentArea);
    }
    else
    {
        const float DesiredLengthCm = MeasurementUnitUtils::UnitToCm(ManualSize, DisplayUnit);
        const float CurrentLength = SplineComponent->GetSplineLength();

        if (CurrentLength <= KINDA_SMALL_NUMBER)
        {
            return;
        }

        ScaleFactor = DesiredLengthCm / CurrentLength;
    }

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    SplineComponent->Modify();

    for (int32 i = 0; i < NumPoints; ++i)
    {
        FVector Location = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
        SplineComponent->SetLocationAtSplinePoint(i, Location * ScaleFactor, ESplineCoordinateSpace::Local, false);

        FVector ArriveTangent = SplineComponent->GetArriveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
        FVector LeaveTangent = SplineComponent->GetLeaveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
        SplineComponent->SetTangentsAtSplinePoint(i, ArriveTangent * ScaleFactor, LeaveTangent * ScaleFactor, ESplineCoordinateSpace::Local, false);
    }

    SplineComponent->UpdateSpline();
    UpdateMeasurementText();
    LabelComponent->UpdateLabels(SplineComponent, MeasurementMode, DisplayUnit);
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

    DrawDebugLine(World, LastPoint, FirstPoint, FColor::Yellow, false, 0.15f, SDPG_World, 2.0f);
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
