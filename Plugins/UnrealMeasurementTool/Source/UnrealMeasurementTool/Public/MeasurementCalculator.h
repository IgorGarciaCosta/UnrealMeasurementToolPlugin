// UnrealMeasurementTool - Measurement Calculator (static utility)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MeasurementUnit.h"
#include "MeasurementCalculator.generated.h"

/**
 * Static utility library for measurement calculations and formatting.
 * All functions are pure — no side effects or state.
 */
UCLASS()
class UNREALMEASUREMENTTOOL_API UMeasurementCalculator : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Calculates the enclosed area (cm²) of a 3D polygon using Newell's method + Shoelace. */
    UFUNCTION(BlueprintCallable, Category = "Measurement|Calculator")
    static float CalculatePolygonArea(const TArray<FVector> &Points);

    /** Returns the angle in degrees between two segments meeting at Current. */
    UFUNCTION(BlueprintCallable, Category = "Measurement|Calculator")
    static float CalculateAngleBetweenSegments(const FVector &Prev, const FVector &Current, const FVector &Next);

    /** Converts a distance in centimeters to the given unit and formats it as text. */
    UFUNCTION(BlueprintCallable, Category = "Measurement|Calculator")
    static FText FormatDistance(float DistanceCm, EMeasurementUnit Unit);

    /** Converts an area in cm² to the given unit² and formats it as text. */
    UFUNCTION(BlueprintCallable, Category = "Measurement|Calculator")
    static FText FormatArea(float AreaCmSq, EMeasurementUnit Unit);

    /** Tries to retrieve the active camera location from the last rendered frame. */
    static bool GetActiveCameraLocation(const UWorld *World, FVector &OutCameraLocation);

    /** Rotates a scene component to face the given camera location (billboard effect). */
    static void FaceComponentToCamera(USceneComponent *Component, const FVector &CameraLocation);
};
