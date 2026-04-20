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

    const float DesiredLengthCm = ManualSizeMeters * 100.0f;
    const float CurrentLength = SplineComponent->GetSplineLength();

    if (CurrentLength <= KINDA_SMALL_NUMBER)
    {
        return;
    }

    const float ScaleFactor = DesiredLengthCm / CurrentLength;
    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();

    for (int32 i = 0; i < NumPoints; ++i)
    {
        FVector Location = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
        SplineComponent->SetLocationAtSplinePoint(i, Location * ScaleFactor, ESplineCoordinateSpace::Local, false);
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
    const float SplineLengthM = SplineLengthCm / 100.0f;

    FNumberFormattingOptions NumberFormat;
    NumberFormat.MinimumFractionalDigits = 2;
    NumberFormat.MaximumFractionalDigits = 2;

    const FText FormattedText = FText::Format(
        NSLOCTEXT("MeasurementActor", "MeasurementFmt", "{0} m"),
        FText::AsNumber(SplineLengthM, &NumberFormat));

    IMeasurementTxtWgtCommunicationInterface::Execute_SendMeasurementText(Widget, FormattedText);
}
