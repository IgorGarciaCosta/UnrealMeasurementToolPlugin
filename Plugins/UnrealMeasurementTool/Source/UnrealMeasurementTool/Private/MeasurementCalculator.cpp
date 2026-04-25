// UnrealMeasurementTool - Measurement Calculator (static utility)

#include "MeasurementCalculator.h"

float UMeasurementCalculator::CalculatePolygonArea(const TArray<FVector> &Points)
{
    const int32 NumPoints = Points.Num();
    if (NumPoints < 3)
    {
        return 0.0f;
    }

    // Compute polygon normal using Newell's method (handles arbitrary 3D polygons).
    FVector Normal = FVector::ZeroVector;
    for (int32 i = 0; i < NumPoints; ++i)
    {
        const FVector &Current = Points[i];
        const FVector &Next = Points[(i + 1) % NumPoints];
        Normal.X += (Current.Y - Next.Y) * (Current.Z + Next.Z);
        Normal.Y += (Current.Z - Next.Z) * (Current.X + Next.X);
        Normal.Z += (Current.X - Next.X) * (Current.Y + Next.Y);
    }

    if (Normal.IsNearlyZero())
    {
        return 0.0f;
    }

    Normal.Normalize();

    // Build a 2D coordinate frame on the polygon's plane.
    FVector UAxis, VAxis;
    Normal.FindBestAxisVectors(UAxis, VAxis);

    // Project points onto the 2D plane and apply the Shoelace formula.
    double Area2D = 0.0;
    for (int32 i = 0; i < NumPoints; ++i)
    {
        const FVector &Current = Points[i];
        const FVector &Next = Points[(i + 1) % NumPoints];

        const double Ui = FVector::DotProduct(Current, UAxis);
        const double Vi = FVector::DotProduct(Current, VAxis);
        const double Uj = FVector::DotProduct(Next, UAxis);
        const double Vj = FVector::DotProduct(Next, VAxis);

        Area2D += (Ui * Vj) - (Uj * Vi);
    }

    return static_cast<float>(FMath::Abs(Area2D) * 0.5);
}

float UMeasurementCalculator::CalculateAngleBetweenSegments(const FVector &Prev, const FVector &Current, const FVector &Next)
{
    const FVector DirToPrev = (Prev - Current).GetSafeNormal();
    const FVector DirToNext = (Next - Current).GetSafeNormal();

    if (DirToPrev.IsNearlyZero() || DirToNext.IsNearlyZero())
    {
        return 0.0f;
    }

    const float Dot = FMath::Clamp(FVector::DotProduct(DirToPrev, DirToNext), -1.0f, 1.0f);
    return FMath::RadiansToDegrees(FMath::Acos(Dot));
}

FText UMeasurementCalculator::FormatDistance(float DistanceCm, EMeasurementUnit Unit)
{
    const float DisplayValue = MeasurementUnitUtils::CmToUnit(DistanceCm, Unit);
    const FString UnitSuffix = MeasurementUnitUtils::GetUnitSuffix(Unit);

    FNumberFormattingOptions NumberFormat;
    NumberFormat.MinimumFractionalDigits = 2;
    NumberFormat.MaximumFractionalDigits = 2;

    return FText::Format(
        NSLOCTEXT("MeasurementCalculator", "MeasurementFmt", "{0} {1}"),
        FText::AsNumber(DisplayValue, &NumberFormat),
        FText::FromString(UnitSuffix));
}

FText UMeasurementCalculator::FormatArea(float AreaCmSq, EMeasurementUnit Unit)
{
    const float DisplayValue = MeasurementUnitUtils::CmSqToUnitSq(AreaCmSq, Unit);
    const FString UnitSuffix = MeasurementUnitUtils::GetUnitSqSuffix(Unit);

    FNumberFormattingOptions NumberFormat;
    NumberFormat.MinimumFractionalDigits = 2;
    NumberFormat.MaximumFractionalDigits = 2;

    return FText::Format(
        NSLOCTEXT("MeasurementCalculator", "AreaFmt", "{0} {1}"),
        FText::AsNumber(DisplayValue, &NumberFormat),
        FText::FromString(UnitSuffix));
}

bool UMeasurementCalculator::GetActiveCameraLocation(const UWorld *World, FVector &OutCameraLocation)
{
    if (!World || World->ViewLocationsRenderedLastFrame.Num() == 0)
    {
        return false;
    }
    OutCameraLocation = World->ViewLocationsRenderedLastFrame[0];
    return true;
}

void UMeasurementCalculator::FaceComponentToCamera(USceneComponent *Component, const FVector &CameraLocation)
{
    if (!IsValid(Component))
    {
        return;
    }
    const FVector Direction = CameraLocation - Component->GetComponentLocation();
    Component->SetWorldRotation(Direction.Rotation());
}
