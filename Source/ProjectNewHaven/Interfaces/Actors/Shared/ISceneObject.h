// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNewHaven/Models/Actors/Shared/SceneObjectModel.h"
#include "UObject/Interface.h"
#include "ISceneObject.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UISceneObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTNEWHAVEN_API IISceneObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ESceneObjectType GetSceneObjectType();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsGrabbed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetGrab(bool bVal);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool HasCollided();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPlayerCharacter_Select();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPlayerCharacter_Deselect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPlayerCharacter_Inspect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPlayerCharacter_Interact();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnBuilderCharacter_Select();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnBuilderCharacter_Deselect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnBuilderCharacter_Inspect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnBuilderCharacter_Interact();
};
