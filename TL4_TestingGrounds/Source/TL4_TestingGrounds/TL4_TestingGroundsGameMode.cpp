// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TL4_TestingGrounds.h"
#include "TL4_TestingGroundsGameMode.h"
#include "TL4_TestingGroundsHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/Paths.h"

ATL4_TestingGroundsGameMode::ATL4_TestingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	const TCHAR* TL4CharacterHardLink = TEXT("/Game/Dynamic/TL4Character/Behaviour/BP_TL4Character");
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TL4CharacterHardLink);
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATL4_TestingGroundsHUD::StaticClass();
}
