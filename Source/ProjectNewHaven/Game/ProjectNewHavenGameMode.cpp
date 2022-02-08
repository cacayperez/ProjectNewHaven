// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectNewHavenGameMode.h"

#include "ProjectNewHaven/Player/PlayerControllerBase.h"
#include "UObject/ConstructorHelpers.h"

AProjectNewHavenGameMode::AProjectNewHavenGameMode()
{
	// set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/NewHaven/Characters/Player/BP_WorldBuilder"));
	PlayerControllerClass = APlayerControllerBase::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/NewHaven/Characters/Player/BP_PlayerCharacter"));
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/NewHaven/TestPawn"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// "/Game/NewHaven/Characters/Player/BP_PlayerCharacter"
// "/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"
// "/Game/NewHaven/Characters/Player/BP_WorldBuilder"
// "/Game/NewHaven/TestPawn.TestPawn"