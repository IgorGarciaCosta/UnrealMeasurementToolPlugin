// UnrealMeasurementTool - Measurement Snap Component

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MeasurementUnit.h"
#include "MeasurementSnapComponent.generated.h"

class USplineComponent;

/**
 * Component that handles snapping spline points to geometry.
 * Supports ground snap (trace down) and nearest surface snap (cardinal traces).
 */
DECLARE_MULTICAST_DELEGATE(FOnMeasurementSnapChanged);

UCLASS(ClassGroup = (Measurement), meta = (BlueprintSpawnableComponent))
class UNREALMEASUREMENTTOOL_API UMeasurementSnapComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMeasurementSnapComponent();

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;

    /** Broadcast when any snap property changes in the editor. */
    FOnMeasurementSnapChanged OnPropertiesChanged;
#endif

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

    /** Snaps all spline points to geometry based on SnapMode. */
    void SnapPoints(USplineComponent *Spline);

    /** Draws debug spheres around each spline point to visualize SnapRadius. */
    void DrawDebugVisualization(const USplineComponent *Spline) const;

private:
    /** Finds the nearest surface hit within a sphere around Origin using cardinal-direction traces. */
    bool FindNearestSurface(UWorld *World, const FVector &Origin, float Radius,
                            ECollisionChannel Channel, const FCollisionQueryParams &Params,
                            FHitResult &OutHit) const;
};
