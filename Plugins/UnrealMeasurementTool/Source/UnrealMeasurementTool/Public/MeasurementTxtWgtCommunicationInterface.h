// UnrealMeasurementTool - Measurement Text Widget Communication Interface

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MeasurementTxtWgtCommunicationInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UMeasurementTxtWgtCommunicationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for sending measurement text to a widget.
 * Any UUserWidget that implements this interface can receive measurement updates
 * without the sender needing to know the concrete widget type.
 */
class UNREALMEASUREMENTTOOL_API IMeasurementTxtWgtCommunicationInterface
{
	GENERATED_BODY()

public:
	/** Sends a formatted measurement text to the implementing widget. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Measurement")
	void SendMeasurementText(const FText& InText);
};
