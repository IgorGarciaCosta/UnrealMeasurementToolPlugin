// UnrealMeasurementTool - Slate Panel for the Measurement Editor Mode

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class FMeasurementEdMode;
class IDetailsView;

class SMeasurementToolkitPanel : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SMeasurementToolkitPanel) {}
    SLATE_END_ARGS()

    void Construct(const FArguments &InArgs, FMeasurementEdMode *InEdMode);

    /** Re-populates the Details View with the currently selected actor. */
    void RefreshDetails();

private:
    FMeasurementEdMode *EdMode = nullptr;
    TSharedPtr<IDetailsView> DetailsView;

    FReply OnAddClicked();
    FReply OnDeleteClicked();
    EVisibility GetDeleteButtonVisibility() const;
};
