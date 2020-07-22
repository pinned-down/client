// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PinnedDown : ModuleRules
{
	public PinnedDown(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "Stomp"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.Add(ModuleDirectory);
    }
}
