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
<<<<<<< HEAD
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Player/Behaviour/FirstPersonCharacter"));
=======
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(*FPaths::GetPath(TEXT("FirstPersonCharacter")));
>>>>>>> origin/master
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATL4_TestingGroundsHUD::StaticClass();
}
