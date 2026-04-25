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
#if WITH_EDITOR
	/** Handle for FEditorDelegates::OnEditorCameraMoved subscription. */
	FDelegateHandle CameraMovedDelegateHandle;
#endif

	/** One-shot timer for deferred snap + debug-draw processing. */
	FTimerHandle DeferredUpdateTimerHandle;

	/** True when snap/labels need to be recalculated (set by OnConstruction, cleared by timer). */
	bool bSnapDirty = false;

	/** Re-entry guard: prevents OnConstruction from re-dirtying while snap is running. */
	bool bIsProcessingSnap = false;

	/** True when debug visualisation needs to be redrawn (persistent lines). */
	bool bDebugDrawDirty = false;

	/** Tracks hidden state so we can flush persistent lines on hide transition. */
	bool bWasHiddenLastFrame = false;

#if WITH_EDITOR
	/** Subscribes to FEditorDelegates::OnEditorCameraMoved if not already bound. */
	void BindEditorCameraDelegate();

	/** Unsubscribes from FEditorDelegates::OnEditorCameraMoved. */
	void UnbindEditorCameraDelegate();

	/** Called when any editor viewport camera moves — faces widget/labels toward camera. */
	void OnCameraLocationChanged(const FVector &CameraLocation);
#endif

	/** Faces widget/labels toward camera and applies distance-based scale. */
	void UpdateBillboard(const FVector &CameraLocation);

	/** Flushes debug draws on hide transition, redraws if dirty and visible. */
	void RefreshDebugDrawIfNeeded();

	/** Flushes all persistent debug lines owned by this world. */
	void FlushDebugDraws() const;

	/** Runs deferred SnapPoints + UpdateLabels when bSnapDirty is set. */
	void ProcessDeferredSnap();

	/** Schedules a one-shot deferred update for snap + debug-draw on the next tick. */
	void ScheduleDeferredUpdate();

	/** One-shot callback: processes snap, orients billboard, redraws debug lines. */
	void ProcessDeferredUpdate();

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
