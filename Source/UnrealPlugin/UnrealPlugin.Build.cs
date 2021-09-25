// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealPlugin : ModuleRules
{
	public UnrealPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"UMG"

			// ... add private dependencies that you statically link with here ...
		});
	}
}
