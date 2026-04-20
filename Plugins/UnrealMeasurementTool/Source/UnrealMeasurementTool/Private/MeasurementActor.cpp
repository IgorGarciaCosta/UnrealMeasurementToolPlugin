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
