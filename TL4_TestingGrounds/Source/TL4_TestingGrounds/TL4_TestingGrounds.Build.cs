// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TL4_TestingGrounds : ModuleRules
{
	public TL4_TestingGrounds(ReadOnlyTargetRules Target) : base(Target)
	{
        // PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivatePCHHeaderFile = "TL4_TestingGrounds.h";
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

		PublicDependencyModuleNames.AddRange
        (new string[]{
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "NavigationSystem",
            "AIModule",
            "GameplayTasks",
            "HeadMountedDisplay"
        });
	}
}
