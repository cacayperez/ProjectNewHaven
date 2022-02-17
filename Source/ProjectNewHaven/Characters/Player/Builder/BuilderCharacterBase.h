// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <ProjectNewHaven/Interfaces/Player/IPlayerPawn.h>

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BuilderCharacterBase.generated.h"

UCLASS()
class PROJECTNEWHAVEN_API ABuilderCharacterBase : public ACharacter, public IIPlayerPawn
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UBuilderInventory* Inventory;
	
	UPROPERTY()
	class AActor* ActiveSceneObject;
	UPROPERTY()
	class AActor* PreviousSceneObject;

	UPROPERTY()
	class APlayerControllerBase* PlayerControllerBase;

	UPROPERTY()
	class APlayerCameraManager* CameraManager;

	
public:
	// Sets default values for this character's properties
	ABuilderCharacterBase();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	class APlayerControllerBase* GetPlayerControllerBase();


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

	UFUNCTION()
	void PlaceActiveSceneObject();

	UFUNCTION()
	void SmoothSnapToCursor(AActor* Actor, const float DeltaTime = 0.0f);

	UFUNCTION()
	void TracePlacementLocation(AActor* Actor, FVector& Location);

};
