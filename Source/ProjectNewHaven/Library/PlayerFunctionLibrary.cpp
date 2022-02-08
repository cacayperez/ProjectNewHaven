﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectNewHaven/Interfaces/Actors/Shared/ISceneObject.h"
#include "ProjectNewHaven/Interfaces/Player/IPlayerInput.h"
#include "ProjectNewHaven/Player/PlayerControllerBase.h"

APawn* UPlayerFunctionLibrary::Pawn_ImplementsPlayerInput(APawn* Pawn)
{
	APawn* SubjectPawn = Pawn;
	
	if(SubjectPawn != nullptr && SubjectPawn->GetClass()->ImplementsInterface(UIPlayerInput::StaticClass()) == true)
	{
		return SubjectPawn;
	}

	return nullptr;
}

AActor* UPlayerFunctionLibrary::Actor_IsSceneObject(AActor* Actor)
{
	AActor* SubjectActor = Actor;
	if(SubjectActor != nullptr && SubjectActor->GetClass()->ImplementsInterface(UISceneObject::StaticClass()) == true)
	{
		return SubjectActor;
	}

	return nullptr;
}

AActor* UPlayerFunctionLibrary::GetObjectOnCursor(APlayerController* Controller)
{
	if(Controller == nullptr) return nullptr;
	
	FHitResult HitResult;
	const bool bHit = Controller->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);

	if(bHit)
	{
		AActor* Actor = HitResult.GetActor();

		return Actor;
	}
	return nullptr;
}

bool UPlayerFunctionLibrary::GetCursorLocation(APlayerController* Controller, FVector& Location)
{
	if(Controller == nullptr) return false;
	
	FHitResult HitResult;
	const bool bHit = Controller->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
	
	if(bHit)
	{
		UPrimitiveComponent* GrabbedComponent = HitResult.GetComponent();
		
		FVector Dir, Loc;
		Controller->DeprojectMousePositionToWorld(Loc, Dir);
		const float Distance = HitResult.Distance;

		Dir = Dir * Distance ;
		Location = Loc + Dir;
		
	}

	return bHit;
}

APawn* UPlayerFunctionLibrary::GetActivePawn(UObject* Context)
{
	const APlayerController* Controller = UGameplayStatics::GetPlayerController(Context, 0);
	if(Controller != nullptr)
	{
		return Controller->GetPawn();
	}

	return nullptr;
}

EGameMode UPlayerFunctionLibrary::GetGameMode(UObject* Context)
{
	const APlayerController* Controller = UGameplayStatics::GetPlayerController(Context, 0);
	EGameMode Mode = EGameMode::None;
	if(Controller != nullptr)
	{
		const APlayerControllerBase* NHController = Cast<APlayerControllerBase>(Controller);

		if(IsValid(NHController))
		{
			Mode = NHController->GetGameMode();
		}
	}

	return Mode;
}