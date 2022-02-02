// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectNewHaven/Interfaces/Characters/Player/IPlayerInput.h"
#include "ControlledCharacterBase.generated.h"

UCLASS()
class PROJECTNEWHAVEN_API AControlledCharacterBase : public ACharacter, public IIPlayerInput
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AControlledCharacterBase();

protected:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
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

	UFUNCTION()
	void Internal_Axis_RightStickX(const float Rate);

	UFUNCTION()
	void Internal_Axis_RightStickY(const float Rate);

	UFUNCTION()
	void Internal_Axis_LeftStickX(const float Rate);

	UFUNCTION()
	void Internal_Axis_LeftStickY(const float Rate);
public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
