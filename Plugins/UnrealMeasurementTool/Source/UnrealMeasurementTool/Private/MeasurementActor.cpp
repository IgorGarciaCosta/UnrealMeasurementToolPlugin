// UnrealMeasurementTool - Measurement Actor

#include "MeasurementActor.h"
#include "Components/SplineComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"
#include "MeasurementTxtWgtCommunicationInterface.h"

AMeasurementActor::AMeasurementActor()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    SetRootComponent(SplineComponent);

    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
    WidgetComponent->SetupAttachment(SplineComponent);
    WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
    WidgetComponent->SetDrawAtDesiredSize(true);
}

void AMeasurementActor::OnConstruction(const FTransform &Transform)
{
    Super::OnConstruction(Transform);
    SnapSplinePoints();
    ApplySplinePointType();
    UpdateMeasurementText();
    UpdatePointLabels();
}

void AMeasurementActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FaceWidgetToCamera();
    FacePointLabelsToCamera();
    DrawSnapRadiusDebug();
    DrawClosingLine();
}

void AMeasurementActor::FaceWidgetToCamera()
{
    if (!WidgetComponent)
    {
        return;
    }

    UWorld *World = GetWorld();
    if (!World || World->ViewLocationsRenderedLastFrame.Num() == 0)
    {
        return;
    }

    const FVector CameraLocation = World->ViewLocationsRenderedLastFrame[0];
    const FVector WidgetLocation = WidgetComponent->GetComponentLocation();
    const FVector Direction = CameraLocation - WidgetLocation;
    WidgetComponent->SetWorldRotation(Direction.Rotation());
}

#if WITH_EDITOR
void AMeasurementActor::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    const FName PropName = PropertyChangedEvent.GetPropertyName();

    if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, ManualSize))
    {
        ApplyManualSize();
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, DisplayUnit))
    {
        UpdateMeasurementText();
        UpdatePointLabels();
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, bShowCumulativeLabels) ||
             PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, CumulativeLabelSize) ||
             PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, CumulativeLabelColor))
    {
        UpdatePointLabels();
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, SnapMode) || PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, SnapRadius) || PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, GroundTraceDistance) || PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, SnapTraceChannel))
    {
        SnapSplinePoints();
        UpdateMeasurementText();
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, bLinearSpline))
    {
        ApplySplinePointType();
        UpdateMeasurementText();
        UpdatePointLabels();
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(AMeasurementActor, MeasurementMode))
    {
        UpdateMeasurementText();
        UpdatePointLabels();
    }
}
#endif

void AMeasurementActor::ResetSpline()
{
    if (!SplineComponent)
    {
        return;
    }

    // Reset actor rotation and scale, keep location
    SetActorRotation(FRotator::ZeroRotator);
    SetActorScale3D(FVector::OneVector);

    // Reset spline to default 2-point configuration
    SplineComponent->ClearSplinePoints(false);
    SplineComponent->AddSplinePoint(FVector(0.f, 0.f, 0.f), ESplineCoordinateSpace::Local, false);
    SplineComponent->AddSplinePoint(FVector(100.f, 0.f, 0.f), ESplineCoordinateSpace::Local, true);

    ApplySplinePointType();
    UpdateMeasurementText();
    UpdatePointLabels();
}

void AMeasurementActor::ApplyManualSize()
{
    if (!SplineComponent)
    {
        return;
    }

    float DesiredLengthCm = 0.0f;

    // In Area mode, ManualSize is a target area — convert to cm² and use sqrt scaling.
    if (MeasurementMode == EMeasurementMode::Area)
    {
        float DesiredAreaCmSq = 0.0f;
        switch (DisplayUnit)
        {
        case EMeasurementUnit::Centimeters:
            DesiredAreaCmSq = ManualSize;
            break;
        case EMeasurementUnit::Meters:
            DesiredAreaCmSq = ManualSize * 10000.0f;
            break;
        case EMeasurementUnit::Kilometers:
            DesiredAreaCmSq = ManualSize * 1e10f;
            break;
        case EMeasurementUnit::Feet:
            DesiredAreaCmSq = ManualSize * 929.0304f;
            break;
        case EMeasurementUnit::Inches:
            DesiredAreaCmSq = ManualSize * 6.4516f;
            break;
        case EMeasurementUnit::Yards:
            DesiredAreaCmSq = ManualSize * 8361.2736f;
            break;
        }

        const float CurrentArea = CalculateEnclosedArea();
        if (CurrentArea <= KINDA_SMALL_NUMBER)
        {
            return;
        }

        const float ScaleFactor = FMath::Sqrt(DesiredAreaCmSq / CurrentArea);
        const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();

        SplineComponent->Modify();

        for (int32 i = 0; i < NumPoints; ++i)
        {
            FVector Location = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
            SplineComponent->SetLocationAtSplinePoint(i, Location * ScaleFactor, ESplineCoordinateSpace::Local, false);

            FVector ArriveTangent = SplineComponent->GetArriveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
            FVector LeaveTangent = SplineComponent->GetLeaveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
            SplineComponent->SetTangentsAtSplinePoint(i, ArriveTangent * ScaleFactor, LeaveTangent * ScaleFactor, ESplineCoordinateSpace::Local, false);
        }

        SplineComponent->UpdateSpline();
        UpdateMeasurementText();
        UpdatePointLabels();
        return;
    }

    switch (DisplayUnit)
    {
    case EMeasurementUnit::Centimeters:
        DesiredLengthCm = ManualSize;
        break;
    case EMeasurementUnit::Meters:
        DesiredLengthCm = ManualSize * 100.0f;
        break;
    case EMeasurementUnit::Kilometers:
        DesiredLengthCm = ManualSize * 100000.0f;
        break;
    case EMeasurementUnit::Feet:
        DesiredLengthCm = ManualSize * 30.48f;
        break;
    case EMeasurementUnit::Inches:
        DesiredLengthCm = ManualSize * 2.54f;
        break;
    case EMeasurementUnit::Yards:
        DesiredLengthCm = ManualSize * 91.44f;
        break;
    }

    const float CurrentLength = SplineComponent->GetSplineLength();

    if (CurrentLength <= KINDA_SMALL_NUMBER)
    {
        return;
    }

    const float ScaleFactor = DesiredLengthCm / CurrentLength;
    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();

    SplineComponent->Modify();

    for (int32 i = 0; i < NumPoints; ++i)
    {
        FVector Location = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
        SplineComponent->SetLocationAtSplinePoint(i, Location * ScaleFactor, ESplineCoordinateSpace::Local, false);

        FVector ArriveTangent = SplineComponent->GetArriveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
        FVector LeaveTangent = SplineComponent->GetLeaveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
        SplineComponent->SetTangentsAtSplinePoint(i, ArriveTangent * ScaleFactor, LeaveTangent * ScaleFactor, ESplineCoordinateSpace::Local, false);
    }

    SplineComponent->UpdateSpline();
    UpdateMeasurementText();
    UpdatePointLabels();
}

void AMeasurementActor::ApplySplinePointType()
{
    if (!SplineComponent)
    {
        return;
    }

    const ESplinePointType::Type PointType = bLinearSpline ? ESplinePointType::Linear : ESplinePointType::Curve;
    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();

    for (int32 i = 0; i < NumPoints; ++i)
    {
        SplineComponent->SetSplinePointType(i, PointType, false);
    }

    SplineComponent->UpdateSpline();
}

void AMeasurementActor::UpdateMeasurementText()
{
    if (!SplineComponent || !WidgetComponent)
    {
        return;
    }

    UUserWidget *Widget = WidgetComponent->GetWidget();
    if (!Widget)
    {
        return;
    }

    if (!Widget->Implements<UMeasurementTxtWgtCommunicationInterface>())
    {
        return;
    }

    const float SplineLengthCm = SplineComponent->GetSplineLength();
    FText FormattedText;

    if (MeasurementMode == EMeasurementMode::Area)
    {
        const float AreaCmSq = CalculateEnclosedArea();
        FormattedText = FormatArea(AreaCmSq);
    }
    else
    {
        FormattedText = FormatDistance(SplineLengthCm);
    }

    IMeasurementTxtWgtCommunicationInterface::Execute_SendMeasurementText(Widget, FormattedText);
}

void AMeasurementActor::SnapSplinePoints()
{
    if (SnapMode == ESnapMode::None || !SplineComponent)
    {
        return;
    }

    UWorld *World = GetWorld();
    if (!World)
    {
        return;
    }

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    if (NumPoints == 0)
    {
        return;
    }

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    SplineComponent->Modify();

    for (int32 i = 0; i < NumPoints; ++i)
    {
        FVector WorldPt = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
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
            const FVector LocalHit = SplineComponent->GetComponentTransform().InverseTransformPosition(Hit.ImpactPoint);
            SplineComponent->SetLocationAtSplinePoint(i, LocalHit, ESplineCoordinateSpace::Local, false);
        }
    }

    SplineComponent->UpdateSpline();
}

bool AMeasurementActor::FindNearestSurface(UWorld *World, const FVector &Origin, float Radius,
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

void AMeasurementActor::DrawSnapRadiusDebug() const
{
    if (!bShowSnapRadius || SnapMode != ESnapMode::SurfaceSnap || !SplineComponent)
    {
        return;
    }

    UWorld *World = GetWorld();
    if (!World)
    {
        return;
    }

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    for (int32 i = 0; i < NumPoints; ++i)
    {
        const FVector WorldPt = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        DrawDebugSphere(World, WorldPt, SnapRadius, 16, FColor::Cyan, false, -1.0f, SDPG_World, 1.0f);
    }
}

FText AMeasurementActor::FormatDistance(float DistanceCm) const
{
    float DisplayValue = 0.0f;
    FString UnitSuffix;

    switch (DisplayUnit)
    {
    case EMeasurementUnit::Centimeters:
        DisplayValue = DistanceCm;
        UnitSuffix = TEXT("cm");
        break;
    case EMeasurementUnit::Meters:
        DisplayValue = DistanceCm / 100.0f;
        UnitSuffix = TEXT("m");
        break;
    case EMeasurementUnit::Kilometers:
        DisplayValue = DistanceCm / 100000.0f;
        UnitSuffix = TEXT("km");
        break;
    case EMeasurementUnit::Feet:
        DisplayValue = DistanceCm / 30.48f;
        UnitSuffix = TEXT("ft");
        break;
    case EMeasurementUnit::Inches:
        DisplayValue = DistanceCm / 2.54f;
        UnitSuffix = TEXT("in");
        break;
    case EMeasurementUnit::Yards:
        DisplayValue = DistanceCm / 91.44f;
        UnitSuffix = TEXT("yd");
        break;
    }

    FNumberFormattingOptions NumberFormat;
    NumberFormat.MinimumFractionalDigits = 2;
    NumberFormat.MaximumFractionalDigits = 2;

    return FText::Format(
        NSLOCTEXT("MeasurementActor", "MeasurementFmt", "{0} {1}"),
        FText::AsNumber(DisplayValue, &NumberFormat),
        FText::FromString(UnitSuffix));
}

void AMeasurementActor::UpdatePointLabels()
{
    if (!SplineComponent)
    {
        return;
    }

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    const int32 DesiredCount = bShowCumulativeLabels ? NumPoints : 0;

    // Remove excess components
    while (PointLabelComponents.Num() > DesiredCount)
    {
        UTextRenderComponent *Comp = PointLabelComponents.Pop();
        if (IsValid(Comp))
        {
            Comp->DestroyComponent();
        }
    }

    // Create missing components
    while (PointLabelComponents.Num() < DesiredCount)
    {
        UTextRenderComponent *NewLabel = NewObject<UTextRenderComponent>(this);
        NewLabel->SetupAttachment(SplineComponent);
        NewLabel->RegisterComponent();
        NewLabel->SetHorizontalAlignment(EHTA_Center);
        NewLabel->SetVerticalAlignment(EVRTA_TextCenter);
        PointLabelComponents.Add(NewLabel);
    }

    // Update each label's position, text, size, and color
    for (int32 i = 0; i < DesiredCount; ++i)
    {
        UTextRenderComponent *Label = PointLabelComponents[i];
        if (!IsValid(Label))
        {
            continue;
        }

        const FVector PointLocation = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
        Label->SetRelativeLocation(PointLocation + FVector(0.0f, 0.0f, 30.0f));

        const float CumulativeDistCm = SplineComponent->GetDistanceAlongSplineAtSplinePoint(i);
        Label->SetText(FormatDistance(CumulativeDistCm));

        Label->SetWorldSize(CumulativeLabelSize);
        Label->SetTextRenderColor(CumulativeLabelColor);
    }
}

void AMeasurementActor::FacePointLabelsToCamera()
{
    if (!bShowCumulativeLabels || PointLabelComponents.Num() == 0)
    {
        return;
    }

    UWorld *World = GetWorld();
    if (!World || World->ViewLocationsRenderedLastFrame.Num() == 0)
    {
        return;
    }

    const FVector CameraLocation = World->ViewLocationsRenderedLastFrame[0];

    for (UTextRenderComponent *Label : PointLabelComponents)
    {
        if (!IsValid(Label))
        {
            continue;
        }

        const FVector LabelLocation = Label->GetComponentLocation();
        const FVector Direction = CameraLocation - LabelLocation;
        Label->SetWorldRotation(Direction.Rotation());
    }
}

float AMeasurementActor::CalculateEnclosedArea() const
{
    if (!SplineComponent)
    {
        return 0.0f;
    }

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    if (NumPoints < 3)
    {
        return 0.0f;
    }

    // Gather world-space positions of all spline points.
    TArray<FVector> Points;
    Points.SetNum(NumPoints);
    for (int32 i = 0; i < NumPoints; ++i)
    {
        Points[i] = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
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

FText AMeasurementActor::FormatArea(float AreaCmSq) const
{
    float DisplayValue = 0.0f;
    FString UnitSuffix;

    switch (DisplayUnit)
    {
    case EMeasurementUnit::Centimeters:
        DisplayValue = AreaCmSq;
        UnitSuffix = TEXT("cm\u00B2");
        break;
    case EMeasurementUnit::Meters:
        DisplayValue = AreaCmSq / 10000.0f;
        UnitSuffix = TEXT("m\u00B2");
        break;
    case EMeasurementUnit::Kilometers:
        DisplayValue = AreaCmSq / 1e10f;
        UnitSuffix = TEXT("km\u00B2");
        break;
    case EMeasurementUnit::Feet:
        DisplayValue = AreaCmSq / 929.0304f;
        UnitSuffix = TEXT("ft\u00B2");
        break;
    case EMeasurementUnit::Inches:
        DisplayValue = AreaCmSq / 6.4516f;
        UnitSuffix = TEXT("in\u00B2");
        break;
    case EMeasurementUnit::Yards:
        DisplayValue = AreaCmSq / 8361.2736f;
        UnitSuffix = TEXT("yd\u00B2");
        break;
    }

    FNumberFormattingOptions NumberFormat;
    NumberFormat.MinimumFractionalDigits = 2;
    NumberFormat.MaximumFractionalDigits = 2;

    return FText::Format(
        NSLOCTEXT("MeasurementActor", "AreaFmt", "{0} {1}"),
        FText::AsNumber(DisplayValue, &NumberFormat),
        FText::FromString(UnitSuffix));
}

void AMeasurementActor::DrawClosingLine() const
{
    if (MeasurementMode != EMeasurementMode::Area || !bShowClosingLine || !SplineComponent)
    {
        return;
    }

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    if (NumPoints < 3)
    {
        return;
    }

    UWorld *World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector FirstPoint = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
    const FVector LastPoint = SplineComponent->GetLocationAtSplinePoint(NumPoints - 1, ESplineCoordinateSpace::World);

    DrawDebugLine(World, LastPoint, FirstPoint, FColor::Yellow, false, -1.0f, SDPG_World, 2.0f);
}
