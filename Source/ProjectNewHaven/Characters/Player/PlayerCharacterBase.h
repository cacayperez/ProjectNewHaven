// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectNewHaven/Interfaces/Actors/Shared/ISceneObject.h"
#include "ProjectNewHaven/Interfaces/Characters/Shared/ICharacter.h"
#include "ProjectNewHaven/Interfaces/Characters/Shared/IInteractivity.h"
#include "ProjectNewHaven/Interfaces/Player/IPlayerPawn.h"
#include "PlayerCharacterBase.generated.h"

UCLASS()
class PROJECTNEWHAVEN_API APlayerCharacterBase : public ACharacter, public IIPlayerPawn, public IICharacter, public IIInteractivity, public IISceneObject
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* _RootComponent;
	
	// /** Loot Box Collision */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	// class UBoxComponent* InteractionBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float CrouchSpeed = 125.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float WalkSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float RunSpeed = 600.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ECharacterMoveState CurrentMoveState;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
public:
	// Sets default values for this character's properties
	APlayerCharacterBase();
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	virtual void PlayerAction_Move_Implementation(const float Value, const EAxis::Type Axis) override;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ECharacterAnimation, UAnimMontage*> CharacterAnimationMap;
};
