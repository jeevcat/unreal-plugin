using UnrealBuildTool;

public class HttpRequests : ModuleRules
{
    public HttpRequests(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"HTTP"
		});

        PublicDependencyModuleNames.AddRange(new[] {
            "CoreUObject",
            "Engine",
        });
    }
}
