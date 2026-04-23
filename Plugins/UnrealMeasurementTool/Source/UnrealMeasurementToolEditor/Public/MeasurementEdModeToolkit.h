// UnrealMeasurementTool - Editor Mode Toolkit (FModeToolkit wrapper)

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/BaseToolkit.h"

class SMeasurementToolkitPanel;

class FMeasurementEdModeToolkit : public FModeToolkit
{
public:
    virtual void Init(const TSharedPtr<IToolkitHost> &InitToolkitHost) override;

    virtual FName GetToolkitFName() const override { return FName("MeasurementEdModeToolkit"); }
    virtual FText GetBaseToolkitName() const override
    {
        return NSLOCTEXT("MeasurementEdMode", "ToolkitName", "Measurement Mode");
    }

    virtual FEdMode *GetEditorMode() const override;
    virtual TSharedPtr<SWidget> GetInlineContent() const override;

    /** Called by the EdMode when the selected actor changes. */
    void RefreshDetailsPanel();

private:
    TSharedPtr<SMeasurementToolkitPanel> PanelWidget;
};
