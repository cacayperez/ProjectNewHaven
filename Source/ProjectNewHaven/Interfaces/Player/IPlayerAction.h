﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPlayerAction.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UIPlayerAction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTNEWHAVEN_API IIPlayerAction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayerAction_OpenMainMenu();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayerAction_Move(const float Value, const EAxis::Type Axis);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayerAction_Interact(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayerAction_Select(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayerAction_Deselect(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayerAction_Inspect(AActor* Actor);
};
