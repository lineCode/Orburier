using UnrealBuildTool;

public class OrburierEditor : ModuleRules
{
    public OrburierEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", 
                "Orburier", 
                "CoreUObject"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "AnimGraph",
                "ApplicationCore",
                "AssetTools",
                "BlueprintGraph",
                "ClassViewer",
                "ContentBrowser",
                "Core",
                "CoreUObject",
                "EditorStyle",
                "EditorWidgets",
                "Engine",
                "GraphEditor",
                "InputCore",
                "Kismet",
                "KismetCompiler",
                "KismetWidgets",
                "MainFrame",
                "Projects",
                "PropertyEditor",
                "RHI",
                "Slate",
                "SlateCore",
                "SourceControl",
                "UnrealEd",
                "WorkspaceMenuStructure",
                "NetCore"
            }
        );
    }
}