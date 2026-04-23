// UnrealMeasurementTool - Slate Panel for the Measurement Editor Mode

#include "SMeasurementToolkitPanel.h"
#include "MeasurementActor.h"
#include "MeasurementSnapComponent.h"
#include "MeasurementLabelComponent.h"

#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "Modules/ModuleManager.h"

#include "Widgets/Input/SButton.h"

#define LOCTEXT_NAMESPACE "SMeasurementToolkitPanel"

FMeasurementEdMode *SMeasurementToolkitPanel::GetEdMode() const
{
    return static_cast<FMeasurementEdMode *>(
        GLevelEditorModeTools().GetActiveMode(EdModeID));
}

void SMeasurementToolkitPanel::Construct(const FArguments &InArgs, FMeasurementEdMode *InEdMode)
{
    EdModeID = InEdMode ? InEdMode->GetID() : FEditorModeID();

    // --- Create a Details View filtered to "Measurement Control" categories only ---
    FDetailsViewArgs DetailsArgs;
    DetailsArgs.bAllowSearch = false;
    DetailsArgs.bShowOptions = false;
    DetailsArgs.bHideSelectionTip = true;
    DetailsArgs.bAllowMultipleTopLevelObjects = true;

    FPropertyEditorModule &PropertyModule =
        FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    DetailsView = PropertyModule.CreateDetailView(DetailsArgs);

    // Only show properties declared directly in our measurement classes
    // (excludes inherited AActor / UActorComponent properties like Transform, Tags, etc.)
    DetailsView->SetIsPropertyVisibleDelegate(
        FIsPropertyVisible::CreateLambda([](const FPropertyAndParent &PropertyAndParent) -> bool
                                         {
			const UStruct* OwnerStruct = PropertyAndParent.Property.GetOwnerStruct();
			if (!OwnerStruct) return false;

			return OwnerStruct->IsChildOf(AMeasurementActor::StaticClass())
				|| OwnerStruct->IsChildOf(UMeasurementSnapComponent::StaticClass())
				|| OwnerStruct->IsChildOf(UMeasurementLabelComponent::StaticClass()); }));

    // --- Build the Slate layout ---
    // NOTE: The engine's FModeToolkit::UpdatePrimaryModePanel() already wraps
    // GetInlineContent() in a SScrollBox, so we must NOT nest another one here.
    ChildSlot
        [SNew(SVerticalBox)

         // ---- Add button ----
         + SVerticalBox::Slot()
               .AutoHeight()
               .Padding(4.0f)
                   [SNew(SButton)
                        .Text(LOCTEXT("AddButton", "+ Add Measurement Instance"))
                        .HAlign(HAlign_Center)
                        .OnClicked(this, &SMeasurementToolkitPanel::OnAddClicked)]

         // ---- Details panel (actor + component properties) ----
         + SVerticalBox::Slot()
               .AutoHeight()
               .Padding(4.0f)
                   [DetailsView.ToSharedRef()]

         // ---- Delete button ----
         + SVerticalBox::Slot()
               .AutoHeight()
               .Padding(4.0f)
                   [SNew(SButton)
                        .Text(LOCTEXT("DeleteButton", "Delete Measurement Actor Instance"))
                        .HAlign(HAlign_Center)
                        .OnClicked(this, &SMeasurementToolkitPanel::OnDeleteClicked)
                        .Visibility(this, &SMeasurementToolkitPanel::GetDeleteButtonVisibility)]];

    // Show the currently selected actor (if any)
    RefreshDetails();
}

// ---------------------------------------------------------------------------

void SMeasurementToolkitPanel::RefreshDetails()
{
    if (!DetailsView.IsValid())
        return;

    FMeasurementEdMode *EdMode = GetEdMode();
    AMeasurementActor *Actor = EdMode ? EdMode->GetSelectedMeasurementActor() : nullptr;

    if (Actor)
    {
        TArray<UObject *> Objects;
        Objects.Add(Actor);

        if (UMeasurementSnapComponent *Snap = Actor->GetComponentByClass<UMeasurementSnapComponent>())
        {
            Objects.Add(Snap);
        }
        if (UMeasurementLabelComponent *Label = Actor->GetComponentByClass<UMeasurementLabelComponent>())
        {
            Objects.Add(Label);
        }

        DetailsView->SetObjects(Objects);
    }
    else
    {
        DetailsView->SetObjects(TArray<UObject *>());
    }
}

// ---------------------------------------------------------------------------
// Button callbacks
// ---------------------------------------------------------------------------

FReply SMeasurementToolkitPanel::OnAddClicked()
{
    if (FMeasurementEdMode *EdMode = GetEdMode())
    {
        EdMode->SpawnMeasurementActor();
    }
    return FReply::Handled();
}

FReply SMeasurementToolkitPanel::OnDeleteClicked()
{
    if (FMeasurementEdMode *EdMode = GetEdMode())
    {
        EdMode->DeleteSelectedActor();
    }
    return FReply::Handled();
}

EVisibility SMeasurementToolkitPanel::GetDeleteButtonVisibility() const
{
    FMeasurementEdMode *EdMode = GetEdMode();
    return (EdMode && EdMode->GetSelectedMeasurementActor())
               ? EVisibility::Visible
               : EVisibility::Collapsed;
}

#undef LOCTEXT_NAMESPACE
