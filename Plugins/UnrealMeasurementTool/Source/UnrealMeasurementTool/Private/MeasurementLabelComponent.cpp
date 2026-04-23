// UnrealMeasurementTool - Measurement Label Component

#include "MeasurementLabelComponent.h"
#include "Components/SplineComponent.h"
#include "Components/TextRenderComponent.h"
#include "MeasurementCalculator.h"

UMeasurementLabelComponent::UMeasurementLabelComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

#if WITH_EDITOR
void UMeasurementLabelComponent::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    OnPropertiesChanged.Broadcast();
}
#endif

void UMeasurementLabelComponent::UpdateLabels(USplineComponent *Spline, EMeasurementMode Mode, EMeasurementUnit Unit)
{
    UpdatePointLabels(Spline, Unit);
    UpdateAngleLabels(Spline, Mode);
}

void UMeasurementLabelComponent::FaceLabelsToCamera(const FVector &CameraLocation)
{
    if (bShowCumulativeLabels)
    {
        for (UTextRenderComponent *Label : PointLabelComponents)
        {
            UMeasurementCalculator::FaceComponentToCamera(Label, CameraLocation);
        }
    }

    if (bShowAngleLabels)
    {
        for (UTextRenderComponent *Label : AngleLabelComponents)
        {
            UMeasurementCalculator::FaceComponentToCamera(Label, CameraLocation);
        }
    }
}

void UMeasurementLabelComponent::UpdatePointLabels(USplineComponent *Spline, EMeasurementUnit Unit)
{
    if (!IsValid(Spline))
    {
        return;
    }

    const int32 NumPoints = Spline->GetNumberOfSplinePoints();
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
        UTextRenderComponent *NewLabel = NewObject<UTextRenderComponent>(GetOwner());
        NewLabel->SetupAttachment(Spline);
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

        const FVector PointLocation = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
        Label->SetRelativeLocation(PointLocation + FVector(0.0f, 0.0f, 30.0f));

        const float CumulativeDistCm = Spline->GetDistanceAlongSplineAtSplinePoint(i);
        Label->SetText(UMeasurementCalculator::FormatDistance(CumulativeDistCm, Unit));

        Label->SetWorldSize(CumulativeLabelSize);
        Label->SetTextRenderColor(CumulativeLabelColor);
    }
}

void UMeasurementLabelComponent::UpdateAngleLabels(USplineComponent *Spline, EMeasurementMode Mode)
{
    if (!IsValid(Spline))
    {
        return;
    }

    const int32 NumPoints = Spline->GetNumberOfSplinePoints();
    const bool bClosed = (Mode == EMeasurementMode::Area);

    // Determine eligible point count
    int32 DesiredCount = 0;
    if (bShowAngleLabels && NumPoints >= 3)
    {
        DesiredCount = bClosed ? NumPoints : (NumPoints - 2);
    }

    // Remove excess components
    while (AngleLabelComponents.Num() > DesiredCount)
    {
        UTextRenderComponent *Comp = AngleLabelComponents.Pop();
        if (IsValid(Comp))
        {
            Comp->DestroyComponent();
        }
    }

    // Create missing components
    while (AngleLabelComponents.Num() < DesiredCount)
    {
        UTextRenderComponent *NewLabel = NewObject<UTextRenderComponent>(GetOwner());
        NewLabel->SetupAttachment(Spline);
        NewLabel->RegisterComponent();
        NewLabel->SetHorizontalAlignment(EHTA_Center);
        NewLabel->SetVerticalAlignment(EVRTA_TextCenter);
        AngleLabelComponents.Add(NewLabel);
    }

    // Update each label
    FNumberFormattingOptions NumberFormat;
    NumberFormat.MinimumFractionalDigits = 1;
    NumberFormat.MaximumFractionalDigits = 1;

    for (int32 LabelIdx = 0; LabelIdx < DesiredCount; ++LabelIdx)
    {
        UTextRenderComponent *Label = AngleLabelComponents[LabelIdx];
        if (!IsValid(Label))
        {
            continue;
        }

        // Map label index to spline point index
        const int32 PointIdx = bClosed ? LabelIdx : (LabelIdx + 1);

        const FVector PointLocation = Spline->GetLocationAtSplinePoint(PointIdx, ESplineCoordinateSpace::Local);
        Label->SetRelativeLocation(PointLocation + FVector(0.0f, 0.0f, AngleLabelZOffset));

        // Get adjacent point indices
        int32 PrevIndex, NextIndex;
        if (bClosed)
        {
            PrevIndex = (PointIdx - 1 + NumPoints) % NumPoints;
            NextIndex = (PointIdx + 1) % NumPoints;
        }
        else
        {
            PrevIndex = PointIdx - 1;
            NextIndex = PointIdx + 1;
        }

        const FVector Prev = Spline->GetLocationAtSplinePoint(PrevIndex, ESplineCoordinateSpace::World);
        const FVector Current = Spline->GetLocationAtSplinePoint(PointIdx, ESplineCoordinateSpace::World);
        const FVector Next = Spline->GetLocationAtSplinePoint(NextIndex, ESplineCoordinateSpace::World);

        const float Angle = UMeasurementCalculator::CalculateAngleBetweenSegments(Prev, Current, Next);
        const FText AngleText = FText::Format(
            NSLOCTEXT("MeasurementLabelComponent", "AngleFmt", "{0}\u00B0"),
            FText::AsNumber(Angle, &NumberFormat));

        Label->SetText(AngleText);
        Label->SetWorldSize(AngleLabelSize);
        Label->SetTextRenderColor(AngleLabelColor);
    }
}
