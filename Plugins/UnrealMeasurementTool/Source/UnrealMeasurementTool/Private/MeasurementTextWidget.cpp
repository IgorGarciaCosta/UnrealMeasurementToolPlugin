// UnrealMeasurementTool - Measurement Text Widget

#include "MeasurementTextWidget.h"
#include "Components/TextBlock.h"

void UMeasurementTextWidget::SetText(const FText &InText)
{
    if (MeasurementText)
    {
        MeasurementText->SetText(InText);
    }
}

void UMeasurementTextWidget::SendMeasurementText_Implementation(const FText &InText)
{
    SetText(InText);
}
