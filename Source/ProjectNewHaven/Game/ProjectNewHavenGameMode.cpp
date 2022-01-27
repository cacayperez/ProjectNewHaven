// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectNewHavenGameMode.h"
#include "UObject/ConstructorHelpers.h"

AProjectNewHavenGameMode::AProjectNewHavenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/NewHaven/Characters/Player/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// "/Game/NewHaven/Characters/Player/BP_PlayerCharacter"
// "/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"