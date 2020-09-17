// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PinnedDown : ModuleRules
{
	public PinnedDown(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnforceIWYU = true;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "HTTP",
            "Json",
            "JsonUtilities",
            "Stomp",
            "UnrealDI"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.Add(ModuleDirectory);
    }
}
