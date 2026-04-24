// UnrealMeasurementTool - Measurement Text Widget

#include "MeasurementTextWidget.h"
#include "Components/TextBlock.h"
#include "Fonts/SlateFontInfo.h"

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

void UMeasurementTextWidget::SendMeasurementFontSize_Implementation(int32 InSize)
{
    if (MeasurementText)
    {
        FSlateFontInfo FontInfo = MeasurementText->GetFont();
        FontInfo.Size = InSize;
        MeasurementText->SetFont(FontInfo);
    }
}
