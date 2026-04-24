// UnrealMeasurementTool - Editor Module

#include "UnrealMeasurementToolEditor.h"
#include "MeasurementEdMode.h"
#include "MeasurementActor.h"
#include "EditorModeRegistry.h"
#include "EngineUtils.h"
#include "Editor.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "FUnrealMeasurementToolEditorModule"

void FUnrealMeasurementToolEditorModule::StartupModule()
{
    FEditorModeRegistry::Get().RegisterMode<FMeasurementEdMode>(
        FMeasurementEdMode::EM_MeasurementModeID,
        LOCTEXT("MeasurementModeName", "Measurement"),
        FSlateIcon(FAppStyle::GetAppStyleSetName(), "EditorViewport.ScaleMode"),
        true);

    // Hide all measurement actors whenever a map is opened (before the mode is activated)
    OnMapOpenedHandle = FEditorDelegates::OnMapOpened.AddLambda([](const FString &, bool)
                                                                {
		UWorld* World = GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
		if (!World) return;

		for (TActorIterator<AMeasurementActor> It(World); It; ++It)
		{
			It->SetIsTemporarilyHiddenInEditor(true);
		} });
}

void FUnrealMeasurementToolEditorModule::ShutdownModule()
{
    FEditorDelegates::OnMapOpened.Remove(OnMapOpenedHandle);
    FEditorModeRegistry::Get().UnregisterMode(FMeasurementEdMode::EM_MeasurementModeID);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealMeasurementToolEditorModule, UnrealMeasurementToolEditor)
