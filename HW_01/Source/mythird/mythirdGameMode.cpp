// Copyright Epic Games, Inc. All Rights Reserved.

#include "mythirdGameMode.h"
#include "mythirdCharacter.h"
#include "UObject/ConstructorHelpers.h"

AmythirdGameMode::AmythirdGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
