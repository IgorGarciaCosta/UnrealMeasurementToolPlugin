using UnrealBuildTool;

public class UnrealMeasurementToolEditor : ModuleRules
{
    public UnrealMeasurementToolEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "UnrealEd",
            "EditorFramework",
            "UnrealMeasurementTool"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Slate",
            "SlateCore",
            "InputCore",
            "LevelEditor",
            "PropertyEditor"
        });
    }
}
