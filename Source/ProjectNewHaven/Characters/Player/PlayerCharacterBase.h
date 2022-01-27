// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectNewHaven/Interfaces/Characters/Player/IPlayerCharacter.h"
#include "ProjectNewHaven/Interfaces/Characters/Player/IPlayerInput.h"
#include "ProjectNewHaven/Interfaces/Characters/Shared/ICharacter.h"
#include "ProjectNewHaven/Interfaces/Characters/Shared/IInteractivity.h"
#include "PlayerCharacterBase.generated.h"

UCLASS()
class PROJECTNEWHAVEN_API APlayerCharacterBase : public ACharacter, public IICharacter, public IIPlayerCharacter, public IIPlayerInput , public IIInteractivity
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Loot Box Collision */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* InteractionBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float CrouchSpeed = 125.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float WalkSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float RunSpeed = 600.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ECharacterMoveState CurrentMoveState;
public:
	// Sets default values for this character's properties
	APlayerCharacterBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ECharacterAnimation, UAnimMontage*> CharacterAnimationMap;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	FORCEINLINE class UBoxComponent* GetInteractionBox() const { return InteractionBox; }
	
protected:

	// Internal Button Functions
	UFUNCTION()
	void Internal_Button_1_Pressed();

	UFUNCTION()
	void Internal_Button_1_Released();

	UFUNCTION()
	void Internal_Button_2_Pressed();

	UFUNCTION()
	void Internal_Button_2_Released();

	UFUNCTION()
	void Internal_Button_3_Pressed();

	UFUNCTION()
	void Internal_Button_3_Released();

	UFUNCTION()
	void Internal_Button_4_Pressed();

	UFUNCTION()
	void Internal_Button_4_Released();

	UFUNCTION()
	void Internal_Axis_RightStickX(const float Rate);

	UFUNCTION()
	void Internal_Axis_RightStickY(const float Rate);

	UFUNCTION()
	void Internal_Axis_LeftStickX(const float Rate);

	UFUNCTION()
	void Internal_Axis_LeftStickY(const float Rate);
	
	UFUNCTION()
	void Internal_Button_5_Pressed();

	UFUNCTION()
	void Internal_Button_5_Released();

	UFUNCTION()
	void Internal_Button_6_Pressed();

	UFUNCTION()
	void Internal_Button_6_Released();
	
	UFUNCTION()
	void Internal_Button_7_Pressed();

	UFUNCTION()
	void Internal_Button_7_Released();

	UFUNCTION()
	void Internal_Button_8_Pressed();

	UFUNCTION()
	void Internal_Button_8_Released();
	

	
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual ECharacterMoveState GetCurrentMoveState_Implementation() override;
	
	virtual float GetWalkSpeed_Implementation() override;
	virtual float GetRunSpeed_Implementation() override;
	virtual float GetCrouchSpeed_Implementation() override;
	virtual bool CanMove_Implementation() override;
	virtual bool IsRunning_Implementation() override;

	virtual void Action_Run_Implementation() override;
	virtual void Action_Walk_Implementation() override;
	virtual void Action_Crouch_Implementation() override;
	virtual void Action_Evade_Implementation(FVector Direction) override;

	virtual void PlayerAction_Move_Implementation(const float Value, const EAxis::Type Axis) override;

	// Input Implementation
	virtual void Input_Button_1_Pressed_Implementation() override;
	// virtual void Input_Button_1_Released_Implementation() override;
	// virtual void Input_Button_2_Pressed_Implementation() override;
	// virtual void Input_Button_2_Released_Implementation() override;
	// virtual void Input_Button_3_Pressed_Implementation() override;
	// virtual void Input_Button_3_Released_Implementation() override;
	virtual void Input_Button_4_Pressed_Implementation() override;
	// virtual void Input_Button_4_Released_Implementation() override;
	// virtual void Input_Button_5_Pressed_Implementation() override;
	// virtual void Input_Button_5_Released_Implementation() override;
	virtual void Input_Button_6_Pressed_Implementation() override; // L2
	// virtual void Input_Button_6_Released_Implementation() override; // L2
	// virtual void Input_Button_7_Pressed_Implementation() override;
	// virtual void Input_Button_7_Released_Implementation() override;
	virtual void Input_Button_8_Pressed_Implementation() override; // R2
	virtual void Input_Button_8_Released_Implementation() override; // R2
	// virtual void Input_Axis_RightStickX_Implementation(const float Rate) override;
	// virtual void Input_Axis_RightStickY_Implementation(const float Rate) override;
	virtual void Input_Axis_LeftStickX_Implementation(const float Rate) override;
	virtual void Input_Axis_LeftStickY_Implementation(const float Rate) override;
};
