// UnrealMeasurementTool - Measurement Snap Component

#include "MeasurementSnapComponent.h"
#include "Components/SplineComponent.h"
#include "DrawDebugHelpers.h"

UMeasurementSnapComponent::UMeasurementSnapComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

#if WITH_EDITOR
void UMeasurementSnapComponent::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    OnPropertiesChanged.Broadcast();
}
#endif

void UMeasurementSnapComponent::SnapPoints(USplineComponent *Spline)
{
    if (SnapMode == ESnapMode::None || !IsValid(Spline))
    {
        return;
    }

    UWorld *World = GetWorld();
    if (!World)
    {
        return;
    }

    const int32 NumPoints = Spline->GetNumberOfSplinePoints();
    if (NumPoints == 0)
    {
        return;
    }

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner());

    Spline->Modify();

    for (int32 i = 0; i < NumPoints; ++i)
    {
        FVector WorldPt = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        FHitResult Hit;
        bool bHit = false;

        if (SnapMode == ESnapMode::GroundSnap)
        {
            const FVector TraceEnd = WorldPt - FVector(0.0f, 0.0f, GroundTraceDistance);
            bHit = World->LineTraceSingleByChannel(Hit, WorldPt, TraceEnd, SnapTraceChannel, QueryParams);
        }
        else if (SnapMode == ESnapMode::SurfaceSnap)
        {
            bHit = FindNearestSurface(World, WorldPt, SnapRadius, SnapTraceChannel, QueryParams, Hit);
        }

        if (bHit)
        {
            const FVector LocalHit = Spline->GetComponentTransform().InverseTransformPosition(Hit.ImpactPoint);
            Spline->SetLocationAtSplinePoint(i, LocalHit, ESplineCoordinateSpace::Local, false);
        }
    }

    Spline->UpdateSpline();
}

bool UMeasurementSnapComponent::FindNearestSurface(UWorld *World, const FVector &Origin, float Radius,
                                                   ECollisionChannel Channel, const FCollisionQueryParams &Params,
                                                   FHitResult &OutHit) const
{
    static const FVector Directions[] = {
        FVector::ForwardVector,
        -FVector::ForwardVector,
        FVector::RightVector,
        -FVector::RightVector,
        FVector::UpVector,
        -FVector::UpVector,
    };

    bool bFoundAny = false;
    float BestDistSq = MAX_FLT;

    for (const FVector &Dir : Directions)
    {
        FHitResult Hit;
        const FVector TraceEnd = Origin + Dir * Radius;

        if (World->LineTraceSingleByChannel(Hit, Origin, TraceEnd, Channel, Params))
        {
            const float DistSq = FVector::DistSquared(Origin, Hit.ImpactPoint);
            if (DistSq < BestDistSq)
            {
                BestDistSq = DistSq;
                OutHit = Hit;
                bFoundAny = true;
            }
        }
    }

    return bFoundAny;
}

void UMeasurementSnapComponent::DrawDebugVisualization(const USplineComponent *Spline) const
{
    if (!bShowSnapRadius || SnapMode != ESnapMode::SurfaceSnap || !IsValid(Spline))
    {
        return;
    }

    UWorld *World = GetWorld();
    if (!World)
    {
        return;
    }

    const int32 NumPoints = Spline->GetNumberOfSplinePoints();
    for (int32 i = 0; i < NumPoints; ++i)
    {
        const FVector WorldPt = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        DrawDebugSphere(World, WorldPt, SnapRadius, 16, FColor::Cyan, true, -1.0f, SDPG_World, 1.0f);
    }
}
