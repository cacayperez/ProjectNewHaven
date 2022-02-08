// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectNewHaven/Models/Settings/GameSetting.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNEWHAVEN_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	APawn* ControlledPawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float BaseCursorSpeed = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	EGameMode CurrentGameMode = EGameMode::Build;
	
public:
	APlayerControllerBase();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

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

	UFUNCTION()
	void MoveCursor(const float Rate, const EAxis::Type Axis);
	
	virtual void SetPawn(APawn* InPawn) override;

public:
	FORCEINLINE EGameMode GetGameMode() const { return CurrentGameMode; };
};