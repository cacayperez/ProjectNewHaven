// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPlayerPawn.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UIPlayerPawn : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTNEWHAVEN_API IIPlayerPawn
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_1_Pressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_1_Released();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_2_Pressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_2_Released();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_3_Pressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_3_Released();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_4_Pressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_4_Released();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_5_Pressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_5_Released();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_6_Pressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_6_Released();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_7_Pressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_7_Released();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_8_Pressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Button_8_Released();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Axis_RightStickX(const float Rate);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Axis_RightStickY(const float Rate);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Axis_LeftStickX(const float Rate);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Axis_LeftStickY(const float Rate);

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
