// UnrealMeasurementTool - Measurement Actor

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeasurementUnit.h"
#include "MeasurementActor.generated.h"

class USplineComponent;
class UWidgetComponent;
class UMeasurementSnapComponent;
class UMeasurementLabelComponent;

/**
 * Actor that uses a SplineComponent to measure distance and displays
 * the result through a WidgetComponent.
 *
 * Communication with the widget is fully decoupled via
 * IMeasurementTxtWgtCommunicationInterface – the actor never references
 * the concrete widget class.
 *
 * Snap logic is delegated to UMeasurementSnapComponent.
 * Label management is delegated to UMeasurementLabelComponent.
 * Calculations / formatting live in UMeasurementCalculator.
 *
 * The measurement updates in the editor when spline points are moved
 * (OnConstruction). Billboard (face-camera) rotation of labels and widget
 * runs on a low-frequency timer (10 Hz) instead of per-frame Tick.
 */
UCLASS()
class UNREALMEASUREMENTTOOL_API AMeasurementActor : public AActor
{
	GENERATED_BODY()

public:
	AMeasurementActor();

	virtual void OnConstruction(const FTransform &Transform) override;
	virtual void Destroyed() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;

private:
	void OnLabelPropertiesChanged();
	void OnSnapPropertiesChanged();
#endif

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Measurement")
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Measurement")
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Measurement")
	TObjectPtr<UMeasurementSnapComponent> SnapComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Measurement")
	TObjectPtr<UMeasurementLabelComponent> LabelComponent;

	/** Resets the spline to its default state (2 points), clears rotation and scale. */
	UFUNCTION(CallInEditor, Category = "Measurement Control", meta = (DisplayName = "Reset"))
	void ResetSpline();

	/** Measurement mode: Distance (spline length) or Area (enclosed polygon). */
	UPROPERTY(EditAnywhere, Category = "Measurement Control", meta = (DisplayName = "Mode"))
	EMeasurementMode MeasurementMode = EMeasurementMode::Distance;

	/** Unit used for the measurement display. */
	UPROPERTY(EditAnywhere, Category = "Measurement Control", meta = (DisplayName = "Unit"))
	EMeasurementUnit DisplayUnit = EMeasurementUnit::Meters;

	/** Size (in the currently selected unit) to apply when Submit is pressed. */
	UPROPERTY(EditAnywhere, Category = "Measurement Control", meta = (DisplayName = "Size", ClampMin = "0.01"))
	float ManualSize = 1.0f;

	/** Rescales the spline so its total length matches ManualSize in the current unit. */
	UFUNCTION(CallInEditor, Category = "Measurement Control", meta = (DisplayName = "Submit"))
	void ApplyManualSize();

	/** When enabled, spline segments are straight lines instead of smooth curves. */
	UPROPERTY(EditAnywhere, Category = "Measurement Control", meta = (DisplayName = "Linear"))
	bool bLinearSpline = false;

	/** Show a debug closing line from the last spline point to the first (Area mode). */
	UPROPERTY(EditAnywhere, Category = "Measurement Control",
			  meta = (DisplayName = "Show Closing Line", EditCondition = "MeasurementMode == EMeasurementMode::Area"))
	bool bShowClosingLine = true;

	/** Font size of the main measurement label. */
	UPROPERTY(EditAnywhere, Category = "Measurement Control",
			  meta = (DisplayName = "Label Font Size", ClampMin = "1", ClampMax = "200"))
	int32 MainLabelFontSize = 24;

private:
	/** Timer handle for the periodic billboard + debug-draw update. */
	FTimerHandle BillboardTimerHandle;

	/** True when snap/labels need to be recalculated (set by OnConstruction, cleared by timer). */
	bool bSnapDirty = false;

	/** Re-entry guard: prevents OnConstruction from re-dirtying while snap is running. */
	bool bIsProcessingSnap = false;

	/** Timer callback: rotates widget/labels to face camera, redraws dirty debug lines. */
	void UpdateBillboard();

	/** Runs deferred SnapPoints + UpdateLabels when bSnapDirty is set. */
	void ProcessDeferredSnap();

	/** Starts the billboard timer if it is not already running. */
	void EnsureBillboardTimer();

	/** Recalculates labels and measurement text in a single call. */
	void RefreshMeasurement();

	/** Reads spline length / area, formats it, and sends to the widget via interface. */
	void UpdateMeasurementText();

	/** Sets all spline points to Linear or Curve based on bLinearSpline. */
	void ApplySplinePointType();

	/** Draws a debug closing line from last spline point to first (Area mode). */
	void DrawClosingLine() const;

	/** Collects world-space positions of all spline points into an array. */
	TArray<FVector> GetSplineWorldPoints() const;
};
