// UnrealMeasurementTool - Measurement Label Component

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MeasurementUnit.h"
#include "MeasurementLabelComponent.generated.h"

class USplineComponent;
class UTextRenderComponent;

/**
 * Component that manages cumulative distance labels and angle labels
 * along a spline. Handles creation, destruction, positioning, formatting,
 * and billboard (face-camera) rotation of UTextRenderComponents.
 */
DECLARE_MULTICAST_DELEGATE(FOnMeasurementLabelChanged);

UCLASS(ClassGroup = (Measurement), meta = (BlueprintSpawnableComponent))
class UNREALMEASUREMENTTOOL_API UMeasurementLabelComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMeasurementLabelComponent();

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;

    /** Broadcast when any label property changes in the editor. */
    FOnMeasurementLabelChanged OnPropertiesChanged;
#endif

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

    // --- Angle Labels ---

    /** When enabled, displays the angle between consecutive segments at each spline point. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Measurement Control|Angle Labels",
              meta = (DisplayName = "Show Angle Labels"))
    bool bShowAngleLabels = false;

    /** World-size of the angle label text. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Measurement Control|Angle Labels",
              meta = (DisplayName = "Label Size", ClampMin = "1.0", EditCondition = "bShowAngleLabels"))
    float AngleLabelSize = 24.0f;

    /** Color of the angle label text. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Measurement Control|Angle Labels",
              meta = (DisplayName = "Label Color", EditCondition = "bShowAngleLabels"))
    FColor AngleLabelColor = FColor::Yellow;

    /** When enabled, draws an arc visualizing the angle between segments. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Measurement Control|Angle Labels",
              meta = (DisplayName = "Show Angle Arcs", EditCondition = "bShowAngleLabels"))
    bool bShowAngleArcs = true;

    /** Radius of the angle arc in world units. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Measurement Control|Angle Labels",
              meta = (DisplayName = "Arc Radius", ClampMin = "1.0", EditCondition = "bShowAngleLabels && bShowAngleArcs"))
    float AngleArcRadius = 25.0f;

    /** Color of the angle arc lines. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Measurement Control|Angle Labels",
              meta = (DisplayName = "Arc Color", EditCondition = "bShowAngleLabels && bShowAngleArcs"))
    FColor AngleArcColor = FColor::Yellow;

    /** Number of line segments used to approximate the arc. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Measurement Control|Angle Labels",
              meta = (DisplayName = "Arc Segments", ClampMin = "4", ClampMax = "64",
                      EditCondition = "bShowAngleLabels && bShowAngleArcs"))
    int32 AngleArcSegments = 16;

    /** Updates all labels (cumulative + angle) based on the current spline state. */
    void UpdateLabels(USplineComponent *Spline, EMeasurementMode Mode, EMeasurementUnit Unit);

    /** Rotates all label components to face the given camera location. */
    void FaceLabelsToCamera(const FVector &CameraLocation);

    /** Draws debug arcs representing the angle at each eligible spline point. */
    void DrawAngleArcs(USplineComponent *Spline, EMeasurementMode Mode) const;

private:
    /** Dynamic array of text render components, one per spline point. */
    UPROPERTY()
    TArray<TObjectPtr<UTextRenderComponent>> PointLabelComponents;

    /** Dynamic array of text render components for angle labels. */
    UPROPERTY()
    TArray<TObjectPtr<UTextRenderComponent>> AngleLabelComponents;

    /** Vertical offset (Z) for angle labels above the spline point. */
    float AngleLabelZOffset = 30.0f;

    /** Creates / destroys / updates cumulative distance labels at each spline point. */
    void UpdatePointLabels(USplineComponent *Spline, EMeasurementUnit Unit);

    /** Creates / destroys / updates angle labels at each eligible spline point. */
    void UpdateAngleLabels(USplineComponent *Spline, EMeasurementMode Mode);
};
