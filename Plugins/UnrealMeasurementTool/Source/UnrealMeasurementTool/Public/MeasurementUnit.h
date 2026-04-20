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
