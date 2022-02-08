// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "GameSetting.generated.h"

UENUM()
enum class EGameMode : uint8
{
	None,
	Adventure,
	Build
};

/**
 * 
 */
UCLASS()
class PROJECTNEWHAVEN_API UGameSetting : public UObject
{
	GENERATED_BODY()
};
