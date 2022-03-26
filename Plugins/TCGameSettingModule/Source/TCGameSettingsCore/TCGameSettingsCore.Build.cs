// Copyright Sam Bonifacio. All Rights Reserved.

using UnrealBuildTool;

public class TCGameSettingsCore : ModuleRules
{
	public TCGameSettingsCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

	}
}
