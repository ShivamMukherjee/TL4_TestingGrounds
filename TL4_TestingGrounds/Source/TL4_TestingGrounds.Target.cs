// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TL4_TestingGroundsTarget : TargetRules
{
	public TL4_TestingGroundsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("TL4_TestingGrounds");
	}
}
