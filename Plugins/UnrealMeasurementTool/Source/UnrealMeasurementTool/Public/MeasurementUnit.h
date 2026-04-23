// UnrealMeasurementTool - Measurement Unit Enum

#pragma once

#include "CoreMinimal.h"
#include "MeasurementUnit.generated.h"

UENUM(BlueprintType)
enum class EMeasurementUnit : uint8
{
    Centimeters UMETA(DisplayName = "cm"),
    Meters UMETA(DisplayName = "m"),
    Kilometers UMETA(DisplayName = "km"),
    Feet UMETA(DisplayName = "ft"),
    Inches UMETA(DisplayName = "in"),
    Yards UMETA(DisplayName = "yd")
};

UENUM(BlueprintType)
enum class EMeasurementMode : uint8
{
    Distance UMETA(DisplayName = "Distance"),
    Area UMETA(DisplayName = "Area"),
};

UENUM(BlueprintType)
enum class ESnapMode : uint8
{
    None UMETA(DisplayName = "Off"),
    GroundSnap UMETA(DisplayName = "Ground (Trace Down)"),
    SurfaceSnap UMETA(DisplayName = "Nearest Surface"),
};

// --- Unit conversion helpers (single source of truth) ---

namespace MeasurementUnitUtils
{
    /** Returns centimeters-per-unit factor for the given unit. */
    inline float GetCmPerUnit(EMeasurementUnit Unit)
    {
        switch (Unit)
        {
        case EMeasurementUnit::Centimeters:
            return 1.0f;
        case EMeasurementUnit::Meters:
            return 100.0f;
        case EMeasurementUnit::Kilometers:
            return 100000.0f;
        case EMeasurementUnit::Feet:
            return 30.48f;
        case EMeasurementUnit::Inches:
            return 2.54f;
        case EMeasurementUnit::Yards:
            return 91.44f;
        default:
            return 1.0f;
        }
    }

    /** Converts a distance in centimeters to the target unit. */
    inline float CmToUnit(float Cm, EMeasurementUnit Unit)
    {
        return Cm / GetCmPerUnit(Unit);
    }

    /** Converts a distance in the given unit to centimeters. */
    inline float UnitToCm(float Value, EMeasurementUnit Unit)
    {
        return Value * GetCmPerUnit(Unit);
    }

    /** Converts an area in cm² to the target unit². */
    inline float CmSqToUnitSq(float CmSq, EMeasurementUnit Unit)
    {
        const float Factor = GetCmPerUnit(Unit);
        return CmSq / (Factor * Factor);
    }

    /** Converts an area in unit² to cm². */
    inline float UnitSqToCmSq(float Value, EMeasurementUnit Unit)
    {
        const float Factor = GetCmPerUnit(Unit);
        return Value * (Factor * Factor);
    }

    /** Returns the linear unit suffix (e.g. "m", "ft"). */
    inline FString GetUnitSuffix(EMeasurementUnit Unit)
    {
        switch (Unit)
        {
        case EMeasurementUnit::Centimeters:
            return TEXT("cm");
        case EMeasurementUnit::Meters:
            return TEXT("m");
        case EMeasurementUnit::Kilometers:
            return TEXT("km");
        case EMeasurementUnit::Feet:
            return TEXT("ft");
        case EMeasurementUnit::Inches:
            return TEXT("in");
        case EMeasurementUnit::Yards:
            return TEXT("yd");
        default:
            return TEXT("");
        }
    }

    /** Returns the squared unit suffix (e.g. "m²", "ft²"). */
    inline FString GetUnitSqSuffix(EMeasurementUnit Unit)
    {
        return GetUnitSuffix(Unit) + TEXT("\u00B2");
    }
}
