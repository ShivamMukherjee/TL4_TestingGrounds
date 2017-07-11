// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TL4_TestingGroundsEditorTarget : TargetRules
{
	public TL4_TestingGroundsEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("TL4_TestingGrounds");
	}
}
