// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "SceneObjectModel.generated.h"

UENUM()
enum class ESceneObjectType
{
	None,
	Fixture,
	Loot,
	Character
};

/**
 * 
 */
UCLASS()
class PROJECTNEWHAVEN_API USceneObjectModel : public UObject
{
	GENERATED_BODY()
};
