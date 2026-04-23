// UnrealMeasurementTool - Measurement Editor Mode

#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"

class AMeasurementActor;

class FMeasurementEdMode : public FEdMode
{
public:
    static const FEditorModeID EM_MeasurementModeID;

    /** Asset path to the Blueprint class used when spawning measurement actors. */
    static const TCHAR *MeasurementActorBlueprintPath;

    // --- Lifecycle ---
    virtual void Enter() override;
    virtual void Exit() override;

    // --- Toolkit (side panel) ---
    virtual bool UsesToolkits() const override { return true; }

    // --- Selection ---
    virtual void ActorSelectionChangeNotify() override;

    // --- Public actions (called from the toolkit panel) ---

    /** Spawns a new AMeasurementActor in front of the active viewport camera. */
    AMeasurementActor *SpawnMeasurementActor();

    /** Destroys the currently selected measurement actor. */
    void DeleteSelectedActor();

    /** Returns the measurement actor currently displayed in the panel. */
    AMeasurementActor *GetSelectedMeasurementActor() const;

private:
    /** Shows or hides every AMeasurementActor in the world. */
    void SetAllMeasurementActorsVisible(bool bVisible);

    /** Picks the first AMeasurementActor found in the world. */
    void SelectFirstAvailableActor();

    /** Tells the toolkit panel to refresh its Details View. */
    void NotifyToolkitRefresh();

    /** Weak reference to avoid dangling pointer if actor is deleted externally. */
    TWeakObjectPtr<AMeasurementActor> SelectedActor;

    /** Cached Blueprint class for spawning (loaded once on first use). */
    TSubclassOf<AMeasurementActor> MeasurementActorBPClass;
};
