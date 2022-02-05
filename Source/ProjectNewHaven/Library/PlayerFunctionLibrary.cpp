// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFunctionLibrary.h"

#include "ProjectNewHaven/Interfaces/Player/IPlayerInput.h"

APawn* UPlayerFunctionLibrary::Pawn_ImplementsPlayerInput(APawn* Pawn)
{
	APawn* SubjectPawn = Pawn;
	
	if(SubjectPawn != nullptr && SubjectPawn->GetClass()->ImplementsInterface(UIPlayerInput::StaticClass()) == true)
	{
		return SubjectPawn;
	}

	return nullptr;
}
