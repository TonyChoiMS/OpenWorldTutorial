
using UnrealBuildTool;

public class TCGameSettingsInput : ModuleRules
{
	public TCGameSettingsInput(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore", "GameplayTags", "DeveloperSettings", "TCGameSettingsCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}