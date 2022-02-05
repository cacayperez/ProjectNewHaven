// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "ProjectNewHaven/Interfaces/Player/IPlayerAction.h"
#include "ProjectNewHaven/Interfaces/Player/IPlayerInput.h"
#include "WorldBuilderBase.generated.h"

UCLASS()
class PROJECTNEWHAVEN_API AWorldBuilderBase : public ADefaultPawn, public IIPlayerInput, public IIPlayerAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float DefaultSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float RunSpeed = 1200.0f;
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* FloatingPawnMovement;
	
public:
	// Sets default values for this pawn's properties
	AWorldBuilderBase();
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	virtual void PlayerAction_Move_Implementation(const float Value, const EAxis::Type Axis) override;
	virtual void Input_Axis_LeftStickX_Implementation(const float Rate) override;
	virtual void Input_Axis_LeftStickY_Implementation(const float Rate) override;
	virtual void Input_Button_8_Pressed_Implementation() override;
	virtual void Input_Button_8_Released_Implementation() override;
};
