﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "SceneObjectModel.generated.h"

UENUM()
enum class ESceneObjectType : uint8
{
	None,
	Fixture,
	Loot,
	Character
};

USTRUCT()
struct FSceneObjectData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ASceneObject* Actor;
};
/**
 * 
 */
UCLASS()
class PROJECTNEWHAVEN_API USceneObjectModel : public UObject
{
	GENERATED_BODY()
};
