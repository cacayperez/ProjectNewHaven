// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "DamageModel.generated.h"

USTRUCT()
struct FDamageData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	
};
/**
 * 
 */
UCLASS()
class PROJECTNEWHAVEN_API UDamageModel : public UObject
{
	GENERATED_BODY()
};
