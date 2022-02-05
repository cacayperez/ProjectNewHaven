// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldBuilderBase.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AWorldBuilderBase::AWorldBuilderBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	bAddDefaultMovementBindings = false;
	// GetMeshComponent()->SetCollisionProfileName("NoCollision");
	GetCollisionComponent()->SetCollisionProfileName("NoCollision");

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMeshComponent());
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagMaxDistance = 30.0f;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	FloatingPawnMovement = Cast<UFloatingPawnMovement>(ADefaultPawn::GetMovementComponent());

	if(FloatingPawnMovement != nullptr)
	{
		FloatingPawnMovement->MaxSpeed = DefaultSpeed;
		// FloatingPawnMovement->Acceleration = 400.0f;
		// FloatingPawnMovement->Deceleration = 400.0f;
	}
}

void AWorldBuilderBase::PlayerAction_Move_Implementation(const float Value, const EAxis::Type Axis)
{
	if(Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Direction
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(Axis);
		
		AddMovementInput(Direction, Value);
	}
}

void AWorldBuilderBase::Input_Axis_LeftStickX_Implementation(const float Rate)
{
	if(Rate != 0.0f)
	{
		Execute_PlayerAction_Move(this, Rate, EAxis::Y);
	}
}

void AWorldBuilderBase::Input_Axis_LeftStickY_Implementation(const float Rate)
{
	if(Rate != 0.0f)
	{
		Execute_PlayerAction_Move(this, Rate, EAxis::X);
	}
}

void AWorldBuilderBase::Input_Button_8_Pressed_Implementation()
{
	if(FloatingPawnMovement != nullptr)
	{
		FloatingPawnMovement->MaxSpeed = RunSpeed;
	}
}

void AWorldBuilderBase::Input_Button_8_Released_Implementation()
{
	if(FloatingPawnMovement != nullptr)
	{
		FloatingPawnMovement->MaxSpeed = DefaultSpeed;
	}
}




