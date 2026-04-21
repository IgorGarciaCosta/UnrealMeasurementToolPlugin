// UnrealMeasurementTool - Measurement Actor

#include "MeasurementActor.h"
#include "Components/SplineComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"
#include "MeasurementTxtWgtCommunicationInterface.h"

AMeasurementActor::AMeasurementActor()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    SetRootComponent(SplineComponent);

    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
    WidgetComponent->SetupAttachment(SplineComponent);
    WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
    WidgetComponent->SetDrawAtDesiredSize(true);
}

void AMeasurementActor::OnConstruction(const FTransform &Transform)
{
    Super::OnConstruction(Transform);
    SnapSplinePoints();
    UpdateMeasurementText();
    UpdatePointLabels();
}

void AMeasurementActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FaceWidgetToCamera();
    FacePointLabelsToCamera();
    DrawSnapRadiusDebug();
}

void AMeasurementActor::FaceWidgetToCamera()
{
    if (!WidgetComponent)
    {
        return;
    }

    UWorld *World = GetWorld();
    if (!World || World->ViewLocationsRenderedLastFrame.Num() == 0)
    {
        return;
    }

    const FVector CameraLocation = World->ViewLocationsRenderedLastFrame[0];
    const FVector WidgetLocation = WidgetComponent->GetComponentLocation();
    const FVector Direction = CameraLocation - WidgetLocation;
    WidgetComponent->SetWorldRotation(Direction.Rotation());
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
        UpdatePointLabels();
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, bShowCumulativeLabels) ||
             PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, CumulativeLabelSize) ||
             PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, CumulativeLabelColor))
    {
        UpdatePointLabels();
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, SnapMode) || PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, SnapRadius) || PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, GroundTraceDistance) || PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, SnapTraceChannel))
    {
        SnapSplinePoints();
        UpdateMeasurementText();
    }
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

    UpdateMeasurementText();
    UpdatePointLabels();
}

void AMeasurementActor::ApplyManualSize()
{
    if (!SplineComponent)
    {
        return;
    }

    float DesiredLengthCm = 0.0f;
    switch (DisplayUnit)
    {
    case EMeasurementUnit::Centimeters:
        DesiredLengthCm = ManualSize;
        break;
    case EMeasurementUnit::Meters:
        DesiredLengthCm = ManualSize * 100.0f;
        break;
    case EMeasurementUnit::Kilometers:
        DesiredLengthCm = ManualSize * 100000.0f;
        break;
    case EMeasurementUnit::Feet:
        DesiredLengthCm = ManualSize * 30.48f;
        break;
    case EMeasurementUnit::Inches:
        DesiredLengthCm = ManualSize * 2.54f;
        break;
    case EMeasurementUnit::Yards:
        DesiredLengthCm = ManualSize * 91.44f;
        break;
    }

    const float CurrentLength = SplineComponent->GetSplineLength();

    if (CurrentLength <= KINDA_SMALL_NUMBER)
    {
        return;
    }

    const float ScaleFactor = DesiredLengthCm / CurrentLength;
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
    UpdatePointLabels();
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

    const float SplineLengthCm = SplineComponent->GetSplineLength();
    const FText FormattedText = FormatDistance(SplineLengthCm);
    IMeasurementTxtWgtCommunicationInterface::Execute_SendMeasurementText(Widget, FormattedText);
}

void AMeasurementActor::SnapSplinePoints()
{
    if (SnapMode == ESnapMode::None || !SplineComponent)
    {
        return;
    }

    UWorld *World = GetWorld();
    if (!World)
    {
        return;
    }

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    if (NumPoints == 0)
    {
        return;
    }

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    SplineComponent->Modify();

    for (int32 i = 0; i < NumPoints; ++i)
    {
        FVector WorldPt = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        FHitResult Hit;
        bool bHit = false;

        if (SnapMode == ESnapMode::GroundSnap)
        {
            const FVector TraceEnd = WorldPt - FVector(0.0f, 0.0f, GroundTraceDistance);
            bHit = World->LineTraceSingleByChannel(Hit, WorldPt, TraceEnd, SnapTraceChannel, QueryParams);
        }
        else if (SnapMode == ESnapMode::SurfaceSnap)
        {
            bHit = FindNearestSurface(World, WorldPt, SnapRadius, SnapTraceChannel, QueryParams, Hit);
        }

        if (bHit)
        {
            const FVector LocalHit = SplineComponent->GetComponentTransform().InverseTransformPosition(Hit.ImpactPoint);
            SplineComponent->SetLocationAtSplinePoint(i, LocalHit, ESplineCoordinateSpace::Local, false);
        }
    }

    SplineComponent->UpdateSpline();
}

bool AMeasurementActor::FindNearestSurface(UWorld *World, const FVector &Origin, float Radius,
                                           ECollisionChannel Channel, const FCollisionQueryParams &Params,
                                           FHitResult &OutHit) const
{
    static const FVector Directions[] = {
        FVector::ForwardVector,
        -FVector::ForwardVector,
        FVector::RightVector,
        -FVector::RightVector,
        FVector::UpVector,
        -FVector::UpVector,
    };

    bool bFoundAny = false;
    float BestDistSq = MAX_FLT;

    for (const FVector &Dir : Directions)
    {
        FHitResult Hit;
        const FVector TraceEnd = Origin + Dir * Radius;

        if (World->LineTraceSingleByChannel(Hit, Origin, TraceEnd, Channel, Params))
        {
            const float DistSq = FVector::DistSquared(Origin, Hit.ImpactPoint);
            if (DistSq < BestDistSq)
            {
                BestDistSq = DistSq;
                OutHit = Hit;
                bFoundAny = true;
            }
        }
    }

    return bFoundAny;
}

void AMeasurementActor::DrawSnapRadiusDebug() const
{
    if (!bShowSnapRadius || SnapMode != ESnapMode::SurfaceSnap || !SplineComponent)
    {
        return;
    }

    UWorld *World = GetWorld();
    if (!World)
    {
        return;
    }

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    for (int32 i = 0; i < NumPoints; ++i)
    {
        const FVector WorldPt = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        DrawDebugSphere(World, WorldPt, SnapRadius, 16, FColor::Cyan, false, -1.0f, SDPG_World, 1.0f);
    }
}

FText AMeasurementActor::FormatDistance(float DistanceCm) const
{
    float DisplayValue = 0.0f;
    FString UnitSuffix;

    switch (DisplayUnit)
    {
    case EMeasurementUnit::Centimeters:
        DisplayValue = DistanceCm;
        UnitSuffix = TEXT("cm");
        break;
    case EMeasurementUnit::Meters:
        DisplayValue = DistanceCm / 100.0f;
        UnitSuffix = TEXT("m");
        break;
    case EMeasurementUnit::Kilometers:
        DisplayValue = DistanceCm / 100000.0f;
        UnitSuffix = TEXT("km");
        break;
    case EMeasurementUnit::Feet:
        DisplayValue = DistanceCm / 30.48f;
        UnitSuffix = TEXT("ft");
        break;
    case EMeasurementUnit::Inches:
        DisplayValue = DistanceCm / 2.54f;
        UnitSuffix = TEXT("in");
        break;
    case EMeasurementUnit::Yards:
        DisplayValue = DistanceCm / 91.44f;
        UnitSuffix = TEXT("yd");
        break;
    }

    FNumberFormattingOptions NumberFormat;
    NumberFormat.MinimumFractionalDigits = 2;
    NumberFormat.MaximumFractionalDigits = 2;

    return FText::Format(
        NSLOCTEXT("MeasurementActor", "MeasurementFmt", "{0} {1}"),
        FText::AsNumber(DisplayValue, &NumberFormat),
        FText::FromString(UnitSuffix));
}

void AMeasurementActor::UpdatePointLabels()
{
    if (!SplineComponent)
    {
        return;
    }

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    const int32 DesiredCount = bShowCumulativeLabels ? NumPoints : 0;

    // Remove excess components
    while (PointLabelComponents.Num() > DesiredCount)
    {
        UTextRenderComponent *Comp = PointLabelComponents.Pop();
        if (IsValid(Comp))
        {
            Comp->DestroyComponent();
        }
    }

    // Create missing components
    while (PointLabelComponents.Num() < DesiredCount)
    {
        UTextRenderComponent *NewLabel = NewObject<UTextRenderComponent>(this);
        NewLabel->SetupAttachment(SplineComponent);
        NewLabel->RegisterComponent();
        NewLabel->SetHorizontalAlignment(EHTA_Center);
        NewLabel->SetVerticalAlignment(EVRTA_TextCenter);
        PointLabelComponents.Add(NewLabel);
    }

    // Update each label's position, text, size, and color
    for (int32 i = 0; i < DesiredCount; ++i)
    {
        UTextRenderComponent *Label = PointLabelComponents[i];
        if (!IsValid(Label))
        {
            continue;
        }

        const FVector PointLocation = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
        Label->SetRelativeLocation(PointLocation + FVector(0.0f, 0.0f, 30.0f));

        const float CumulativeDistCm = SplineComponent->GetDistanceAlongSplineAtSplinePoint(i);
        Label->SetText(FormatDistance(CumulativeDistCm));

        Label->SetWorldSize(CumulativeLabelSize);
        Label->SetTextRenderColor(CumulativeLabelColor);
    }
}

void AMeasurementActor::FacePointLabelsToCamera()
{
    if (!bShowCumulativeLabels || PointLabelComponents.Num() == 0)
    {
        return;
    }

    UWorld *World = GetWorld();
    if (!World || World->ViewLocationsRenderedLastFrame.Num() == 0)
    {
        return;
    }

    const FVector CameraLocation = World->ViewLocationsRenderedLastFrame[0];

    for (UTextRenderComponent *Label : PointLabelComponents)
    {
        if (!IsValid(Label))
        {
            continue;
        }

        const FVector LabelLocation = Label->GetComponentLocation();
        const FVector Direction = CameraLocation - LabelLocation;
        Label->SetWorldRotation(Direction.Rotation());
    }
}
