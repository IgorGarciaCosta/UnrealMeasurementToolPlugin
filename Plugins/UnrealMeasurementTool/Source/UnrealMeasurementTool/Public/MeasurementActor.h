// UnrealMeasurementTool - Measurement Actor

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeasurementUnit.h"
#include "MeasurementActor.generated.h"

class USplineComponent;
class UTextRenderComponent;
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

	// --- Snap Settings ---

	/** How spline points should snap to geometry. */
	UPROPERTY(EditAnywhere, Category = "Measurement Control")
	ESnapMode SnapMode = ESnapMode::None;

	/** Maximum distance to search for surfaces (SurfaceSnap only). */
	UPROPERTY(EditAnywhere, Category = "Measurement Control",
			  meta = (EditCondition = "SnapMode == ESnapMode::SurfaceSnap", ClampMin = "1.0"))
	float SnapRadius = 50.0f;

	/** Maximum downward trace distance (GroundSnap only). */
	UPROPERTY(EditAnywhere, Category = "Measurement Control",
			  meta = (EditCondition = "SnapMode == ESnapMode::GroundSnap", ClampMin = "1.0"))
	float GroundTraceDistance = 10000.0f;

	/** Collision channel used for snap traces. */
	UPROPERTY(EditAnywhere, Category = "Measurement Control",
			  meta = (EditCondition = "SnapMode != ESnapMode::None"))
	TEnumAsByte<ECollisionChannel> SnapTraceChannel = ECC_WorldStatic;

	/** Show debug spheres to visualize SnapRadius around each spline point. */
	UPROPERTY(EditAnywhere, Category = "Measurement Control",
			  meta = (EditCondition = "SnapMode == ESnapMode::SurfaceSnap", DisplayName = "Show Snap Radius"))
	bool bShowSnapRadius = false;

	// --- Cumulative Labels ---

	/** When enabled, displays the accumulated distance at each spline point. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Measurement Control|Cumulative Labels",
			  meta = (DisplayName = "Show Cumulative Labels"))
	bool bShowCumulativeLabels = false;

	/** World-size of the cumulative label text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Measurement Control|Cumulative Labels",
			  meta = (DisplayName = "Label Size", ClampMin = "1.0", EditCondition = "bShowCumulativeLabels"))
	float CumulativeLabelSize = 24.0f;

	/** Color of the cumulative label text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Measurement Control|Cumulative Labels",
			  meta = (DisplayName = "Label Color", EditCondition = "bShowCumulativeLabels"))
	FColor CumulativeLabelColor = FColor::White;

private:
	/** Dynamic array of text render components, one per spline point. */
	UPROPERTY()
	TArray<TObjectPtr<UTextRenderComponent>> PointLabelComponents;
	/** Reads spline length, converts to meters, and sends to the widget via interface. */
	void UpdateMeasurementText();

	/** Rotates the widget to always face the camera (billboard). */
	void FaceWidgetToCamera();

	/** Snaps all spline points to geometry based on SnapMode. */
	void SnapSplinePoints();

	/** Finds the nearest surface hit within a sphere around Origin using cardinal-direction traces. */
	bool FindNearestSurface(UWorld *World, const FVector &Origin, float Radius,
							ECollisionChannel Channel, const FCollisionQueryParams &Params,
							FHitResult &OutHit) const;

	/** Draws debug spheres around each spline point to visualize SnapRadius. */
	void DrawSnapRadiusDebug() const;

	/** Creates / destroys / updates cumulative distance labels at each spline point. */
	void UpdatePointLabels();

	/** Converts a distance in centimeters to the current DisplayUnit and appends the suffix. */
	FText FormatDistance(float DistanceCm) const;
	alignas

		/** Rotates all point label components to face the camera. */
		void
		FacePointLabelsToCamera();
};
