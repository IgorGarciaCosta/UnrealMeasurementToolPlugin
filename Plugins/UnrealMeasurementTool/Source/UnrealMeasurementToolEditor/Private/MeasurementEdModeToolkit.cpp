// UnrealMeasurementTool - Editor Mode Toolkit

#include "MeasurementEdModeToolkit.h"
#include "SMeasurementToolkitPanel.h"
#include "MeasurementEdMode.h"
#include "EditorModeManager.h"

void FMeasurementEdModeToolkit::Init(const TSharedPtr<IToolkitHost> &InitToolkitHost)
{
    FModeToolkit::Init(InitToolkitHost);

    FMeasurementEdMode *EdMode = static_cast<FMeasurementEdMode *>(
        GLevelEditorModeTools().GetActiveMode(FMeasurementEdMode::EM_MeasurementModeID));

    PanelWidget = SNew(SMeasurementToolkitPanel, EdMode);
}

FEdMode *FMeasurementEdModeToolkit::GetEditorMode() const
{
    return GLevelEditorModeTools().GetActiveMode(FMeasurementEdMode::EM_MeasurementModeID);
}

TSharedPtr<SWidget> FMeasurementEdModeToolkit::GetInlineContent() const
{
    return PanelWidget;
}

void FMeasurementEdModeToolkit::RefreshDetailsPanel()
{
    if (PanelWidget.IsValid())
    {
        PanelWidget->RefreshDetails();
    }
}
