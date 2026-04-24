// UnrealMeasurementTool - Measurement Text Widget

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MeasurementTxtWgtCommunicationInterface.h"
#include "MeasurementTextWidget.generated.h"

class UTextBlock;

/**
 * Widget that displays a measurement text value.
 * Implements IMeasurementTxtWgtCommunicationInterface so that any actor can send
 * measurement data without knowing the concrete widget type.
 *
 * Usage: Create a Widget Blueprint based on this class and add a TextBlock named "MeasurementText".
 */
UCLASS()
class UNREALMEASUREMENTTOOL_API UMeasurementTextWidget : public UUserWidget, public IMeasurementTxtWgtCommunicationInterface
{
	GENERATED_BODY()

public:
	/** Sets the measurement display text. */
	UFUNCTION(BlueprintCallable, Category = "Measurement")
	void SetText(const FText &InText);

protected:
	// --- IMeasurementTxtWgtCommunicationInterface ---
	virtual void SendMeasurementText_Implementation(const FText &InText) override;
	virtual void SendMeasurementFontSize_Implementation(int32 InSize) override;

	/** Bound text block – must exist in the Widget Blueprint with this exact name. */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MeasurementText;
};
