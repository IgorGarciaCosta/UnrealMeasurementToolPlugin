// UnrealMeasurementTool - Measurement Actor

#include "MeasurementActor.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"
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
}

void AMeasurementActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FaceWidgetToCamera();
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

    float DisplayValue = 0.0f;
    FString UnitSuffix;

    switch (DisplayUnit)
    {
    case EMeasurementUnit::Centimeters:
        DisplayValue = SplineLengthCm;
        UnitSuffix = TEXT("cm");
        break;
    case EMeasurementUnit::Meters:
        DisplayValue = SplineLengthCm / 100.0f;
        UnitSuffix = TEXT("m");
        break;
    case EMeasurementUnit::Kilometers:
        DisplayValue = SplineLengthCm / 100000.0f;
        UnitSuffix = TEXT("km");
        break;
    case EMeasurementUnit::Feet:
        DisplayValue = SplineLengthCm / 30.48f;
        UnitSuffix = TEXT("ft");
        break;
    case EMeasurementUnit::Inches:
        DisplayValue = SplineLengthCm / 2.54f;
        UnitSuffix = TEXT("in");
        break;
    case EMeasurementUnit::Yards:
        DisplayValue = SplineLengthCm / 91.44f;
        UnitSuffix = TEXT("yd");
        break;
    }

    FNumberFormattingOptions NumberFormat;
    NumberFormat.MinimumFractionalDigits = 2;
    NumberFormat.MaximumFractionalDigits = 2;

    const FText FormattedText = FText::Format(
        NSLOCTEXT("MeasurementActor", "MeasurementFmt", "{0} {1}"),
        FText::AsNumber(DisplayValue, &NumberFormat),
        FText::FromString(UnitSuffix));

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
