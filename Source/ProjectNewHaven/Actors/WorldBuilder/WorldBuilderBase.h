// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "ProjectNewHaven/Interfaces/Player/IPlayerPawn.h"
#include "ProjectNewHaven/Player/PlayerControllerBase.h"
#include "WorldBuilderBase.generated.h"

UCLASS()
class PROJECTNEWHAVEN_API AWorldBuilderBase : public ADefaultPawn, public IIPlayerPawn
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

	UPROPERTY()
	class AActor* ActiveSceneObject;

	UPROPERTY()
	class APlayerControllerBase* PlayerControllerBase;
	
public:
	// Sets default values for this pawn's properties
	AWorldBuilderBase();
	
	virtual void Tick(float DeltaSeconds) override;
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE class APlayerControllerBase* GetPlayerControllerBase()
	{
		if(PlayerControllerBase == nullptr && Controller != nullptr)
		{
			PlayerControllerBase = Cast<APlayerControllerBase>(Controller);
		}

		return PlayerControllerBase;
	}

	virtual void PlayerAction_Move_Implementation(const float Value, const EAxis::Type Axis) override;
	virtual void PlayerAction_Interact_Implementation(AActor* Actor) override;
	virtual void PlayerAction_Select_Implementation(AActor* Actor) override;
	virtual void PlayerAction_Deselect_Implementation(AActor* Actor) override;

	virtual void Input_Axis_LeftStickX_Implementation(const float Rate) override;
	virtual void Input_Axis_LeftStickY_Implementation(const float Rate) override;
	virtual void Input_Button_3_Pressed_Implementation() override;

	virtual void Input_Button_8_Pressed_Implementation() override;
	virtual void Input_Button_8_Released_Implementation() override;

	UFUNCTION()
	void GrabSceneObject(AActor* Actor);

};
