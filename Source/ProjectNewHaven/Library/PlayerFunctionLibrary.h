// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNEWHAVEN_API UPlayerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static APawn* Pawn_ImplementsPlayerInput(APawn* Pawn);
};
