// UnrealMeasurementTool - Measurement Actor

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeasurementUnit.h"
#include "MeasurementActor.generated.h"

class USplineComponent;
class UWidgetComponent;

/**
 * Actor that uses a SplineComponent to measure distance and displays
 * the result through a WidgetComponent.
 *
 * Communication with the widget is fully decoupled via
 * IMeasurementTxtWgtCommunicationInterface – the actor never references
 * the concrete widget class.
 *
 * The measurement updates in the editor when spline points are moved
 * (OnConstruction). No Tick overhead at runtime.
 */
UCLASS()
class UNREALMEASUREMENTTOOL_API AMeasurementActor : public AActor
{
	GENERATED_BODY()

public:
	AMeasurementActor();

	virtual void OnConstruction(const FTransform &Transform) override;
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override { return true; }

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
#endif

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Measurement")
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Measurement")
	TObjectPtr<UWidgetComponent> WidgetComponent;

	/** Resets the spline to its default state (2 points), clears rotation and scale. */
	UFUNCTION(CallInEditor, Category = "Measurement Control", meta = (DisplayName = "Reset"))
	void ResetSpline();

	/** Unit used for the measurement display. */
	UPROPERTY(EditAnywhere, Category = "Measurement Control", meta = (DisplayName = "Unit"))
	EMeasurementUnit DisplayUnit = EMeasurementUnit::Meters;

	/** Size (in the currently selected unit) to apply when Submit is pressed. */
	UPROPERTY(EditAnywhere, Category = "Measurement Control", meta = (DisplayName = "Size", ClampMin = "0.01"))
	float ManualSize = 1.0f;

	/** Rescales the spline so its total length matches ManualSizeMeters. */
	UFUNCTION(CallInEditor, Category = "Measurement Control", meta = (DisplayName = "Submit"))
	void ApplyManualSize();

private:
	/** Reads spline length, converts to meters, and sends to the widget via interface. */
	void UpdateMeasurementText();

	/** Rotates the widget to always face the camera (billboard). */
	void FaceWidgetToCamera();
};
