// UnrealMeasurementTool - Measurement Editor Mode

#include "MeasurementEdMode.h"
#include "MeasurementEdModeToolkit.h"
#include "MeasurementActor.h"
#include "EngineUtils.h"
#include "Editor.h"
#include "EditorModeManager.h"
#include "Engine/Selection.h"
#include "LevelEditorViewport.h"
#include "ScopedTransaction.h"

const FEditorModeID FMeasurementEdMode::EM_MeasurementModeID = TEXT("EM_MeasurementMode");
const TCHAR *FMeasurementEdMode::MeasurementActorBlueprintPath =
    TEXT("/UnrealMeasurementTool/BP_MeasurementActor.BP_MeasurementActor_C");

// ---------------------------------------------------------------------------
// Lifecycle
// ---------------------------------------------------------------------------

void FMeasurementEdMode::Enter()
{
    FEdMode::Enter();

    SetAllMeasurementActorsVisible(true);
    SelectFirstAvailableActor();

    if (!Toolkit.IsValid())
    {
        TSharedPtr<FMeasurementEdModeToolkit> ModeToolkit = MakeShared<FMeasurementEdModeToolkit>();
        ModeToolkit->Init(Owner->GetToolkitHost());
        Toolkit = ModeToolkit;
    }
}

void FMeasurementEdMode::Exit()
{
    SetAllMeasurementActorsVisible(false);
    SelectedActor.Reset();
    Toolkit.Reset();

    FEdMode::Exit();
}

// ---------------------------------------------------------------------------
// Selection
// ---------------------------------------------------------------------------

void FMeasurementEdMode::ActorSelectionChangeNotify()
{
    FEdMode::ActorSelectionChangeNotify();

    USelection *Selection = GEditor->GetSelectedActors();
    if (!Selection)
        return;

    for (FSelectionIterator It(*Selection); It; ++It)
    {
        if (AMeasurementActor *MeasurementActor = Cast<AMeasurementActor>(*It))
        {
            SelectedActor = MeasurementActor;
            NotifyToolkitRefresh();
            return;
        }
    }

    // No measurement actor in the current selection — keep previous
}

// ---------------------------------------------------------------------------
// Public actions
// ---------------------------------------------------------------------------

AMeasurementActor *FMeasurementEdMode::SpawnMeasurementActor()
{
    UWorld *World = GetWorld();
    if (!World)
        return nullptr;

    // Spawn 500 units in front of the active editor viewport camera
    FVector SpawnLocation = FVector::ZeroVector;
    if (GCurrentLevelEditingViewportClient)
    {
        const FVector CamLoc = GCurrentLevelEditingViewportClient->GetViewLocation();
        const FRotator CamRot = GCurrentLevelEditingViewportClient->GetViewRotation();
        SpawnLocation = CamLoc + CamRot.Vector() * 500.0f;
    }

    // Load the Blueprint class on first use
    if (!MeasurementActorBPClass)
    {
        MeasurementActorBPClass = LoadClass<AMeasurementActor>(nullptr, MeasurementActorBlueprintPath);
        if (!MeasurementActorBPClass)
        {
            UE_LOG(LogTemp, Error, TEXT("MeasurementEdMode: Failed to load BP class '%s'. Falling back to C++ class."), MeasurementActorBlueprintPath);
            MeasurementActorBPClass = AMeasurementActor::StaticClass();
        }
    }

    FScopedTransaction Transaction(NSLOCTEXT("MeasurementEdMode", "SpawnActor", "Spawn Measurement Actor"));

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AMeasurementActor *NewActor = World->SpawnActor<AMeasurementActor>(
        MeasurementActorBPClass, FTransform(SpawnLocation), Params);

    if (NewActor)
    {
        SelectedActor = NewActor;

        // Select the new actor in the editor so transform gizmos work
        GEditor->SelectNone(true, true);
        GEditor->SelectActor(NewActor, true, true);

        NotifyToolkitRefresh();
    }

    return NewActor;
}

void FMeasurementEdMode::DeleteSelectedActor()
{
    AMeasurementActor *Actor = SelectedActor.Get();
    if (!Actor)
        return;

    FScopedTransaction Transaction(NSLOCTEXT("MeasurementEdMode", "DeleteActor", "Delete Measurement Actor"));

    GEditor->SelectNone(true, true);
    Actor->Destroy();
    SelectedActor.Reset();

    SelectFirstAvailableActor();
    NotifyToolkitRefresh();
}

AMeasurementActor *FMeasurementEdMode::GetSelectedMeasurementActor() const
{
    return SelectedActor.Get();
}

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

void FMeasurementEdMode::SetAllMeasurementActorsVisible(bool bVisible)
{
    UWorld *World = GetWorld();
    if (!World)
        return;

    for (TActorIterator<AMeasurementActor> It(World); It; ++It)
    {
        It->SetIsTemporarilyHiddenInEditor(!bVisible);
    }
}

void FMeasurementEdMode::SelectFirstAvailableActor()
{
    UWorld *World = GetWorld();
    if (!World)
        return;

    for (TActorIterator<AMeasurementActor> It(World); It; ++It)
    {
        SelectedActor = *It;
        return;
    }
}

void FMeasurementEdMode::NotifyToolkitRefresh()
{
    if (Toolkit.IsValid())
    {
        StaticCastSharedPtr<FMeasurementEdModeToolkit>(Toolkit)->RefreshDetailsPanel();
    }
}
