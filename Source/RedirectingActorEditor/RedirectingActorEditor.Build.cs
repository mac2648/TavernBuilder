using UnrealBuildTool;

public class RedirectingActorEditor : ModuleRules
{
    public RedirectingActorEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange( new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UnrealEd", "EditorScriptingUtilities", "EditorFramework", "SlateCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}