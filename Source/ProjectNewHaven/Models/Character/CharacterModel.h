// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CharacterModel.generated.h"

UENUM()
enum class ECharacterEmote :  uint8
{
	None,
	Happy,
	Sad,
	Afraid,
	Surprised,
	Angry,
	Disgusted
};

UENUM()
enum class ECharacterAnimation :  uint8
{
	None,
	DodgeRoll
};

UENUM()
enum class ECharacterMoveState : uint8
{
	None,
	Crouching,
	Walking,
	Running,
	TakingCover,
	Evading,
	Restrained,
	TakingDamage
};

/**
 * 
 */
UCLASS()
class PROJECTNEWHAVEN_API UCharacterModel : public UObject
{
	GENERATED_BODY()
};
