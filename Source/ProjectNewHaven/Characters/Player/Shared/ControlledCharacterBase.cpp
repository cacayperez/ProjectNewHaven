// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlledCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ProjectNewHaven/Config/InputDefinitions.h"


// Sets default values
AControlledCharacterBase::AControlledCharacterBase()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
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
}
// Internal Input Functions
void AControlledCharacterBase::Internal_Button_1_Pressed()
{
	Execute_Input_Button_1_Pressed(this);
}

void AControlledCharacterBase::Internal_Button_1_Released()
{
	Execute_Input_Button_1_Released(this);
}

void AControlledCharacterBase::Internal_Button_2_Pressed()
{
	Execute_Input_Button_2_Pressed(this);
}

void AControlledCharacterBase::Internal_Button_2_Released()
{
	Execute_Input_Button_2_Released(this);
}

void AControlledCharacterBase::Internal_Button_3_Pressed()
{
	Execute_Input_Button_3_Pressed(this);
}

void AControlledCharacterBase::Internal_Button_3_Released()
{
	Execute_Input_Button_3_Released(this);
}

void AControlledCharacterBase::Internal_Button_4_Pressed()
{
	Execute_Input_Button_4_Pressed(this);
}

void AControlledCharacterBase::Internal_Button_4_Released()
{
	Execute_Input_Button_4_Released(this);
}

void AControlledCharacterBase::Internal_Button_5_Pressed()
{
	Execute_Input_Button_5_Pressed(this);
}

void AControlledCharacterBase::Internal_Button_5_Released()
{
	Execute_Input_Button_5_Released(this);
}

void AControlledCharacterBase::Internal_Button_6_Pressed()
{
	Execute_Input_Button_6_Pressed(this);
}

void AControlledCharacterBase::Internal_Button_6_Released()
{
	Execute_Input_Button_6_Released(this);
}

void AControlledCharacterBase::Internal_Button_7_Pressed()
{
	Execute_Input_Button_7_Pressed(this);
}

void AControlledCharacterBase::Internal_Button_7_Released()
{
	Execute_Input_Button_7_Released(this);
}

void AControlledCharacterBase::Internal_Button_8_Pressed()
{
	Execute_Input_Button_8_Pressed(this);
}

void AControlledCharacterBase::Internal_Button_8_Released()
{
	Execute_Input_Button_8_Released(this);
}

void AControlledCharacterBase::Internal_Axis_LeftStickX(const float Rate)
{
	Execute_Input_Axis_LeftStickX(this, Rate);
}

void AControlledCharacterBase::Internal_Axis_LeftStickY(const float Rate)
{
	Execute_Input_Axis_LeftStickY(this, Rate);
}

void AControlledCharacterBase::Internal_Axis_RightStickX(const float Rate)
{
	Execute_Input_Axis_RightStickX(this, Rate);
}

void AControlledCharacterBase::Internal_Axis_RightStickY(const float Rate)
{
	Execute_Input_Axis_RightStickY(this, Rate);
}

// Called to bind functionality to input
void AControlledCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis Left
	// For Forward and Right Movement
	PlayerInputComponent->BindAxis(INPUT_AXIS_LEFT_Y, this, &AControlledCharacterBase::Internal_Axis_LeftStickY);
	PlayerInputComponent->BindAxis(INPUT_AXIS_LEFT_X, this, &AControlledCharacterBase::Internal_Axis_LeftStickX);

	// Axis Right
	// For Character Rotation
	PlayerInputComponent->BindAxis(INPUT_AXIS_RIGHT_Y, this, &AControlledCharacterBase::Internal_Axis_RightStickY);
	PlayerInputComponent->BindAxis(INPUT_AXIS_RIGHT_X, this, &AControlledCharacterBase::Internal_Axis_RightStickX);

	// Triangle
	PlayerInputComponent->BindAction(INPUT_BUTTON_1 , IE_Pressed, this, &AControlledCharacterBase::Internal_Button_1_Pressed);
	PlayerInputComponent->BindAction(INPUT_BUTTON_1, IE_Released, this, &AControlledCharacterBase::Internal_Button_1_Released);

	// Circle
	PlayerInputComponent->BindAction(INPUT_BUTTON_2 , IE_Pressed, this, &AControlledCharacterBase::Internal_Button_2_Pressed);
	PlayerInputComponent->BindAction(INPUT_BUTTON_2, IE_Released, this, &AControlledCharacterBase::Internal_Button_2_Released);

	// Square
	PlayerInputComponent->BindAction(INPUT_BUTTON_3 , IE_Pressed, this, &AControlledCharacterBase::Internal_Button_3_Pressed);
	PlayerInputComponent->BindAction(INPUT_BUTTON_3, IE_Released, this, &AControlledCharacterBase::Internal_Button_3_Released);

	// Cross
	PlayerInputComponent->BindAction(INPUT_BUTTON_4 , IE_Pressed, this, &AControlledCharacterBase::Internal_Button_4_Pressed);
	PlayerInputComponent->BindAction(INPUT_BUTTON_4, IE_Released, this, &AControlledCharacterBase::Internal_Button_4_Released);

	// Left Trigger 1
	PlayerInputComponent->BindAction(INPUT_BUTTON_5 , IE_Pressed, this, &AControlledCharacterBase::Internal_Button_5_Pressed);
	PlayerInputComponent->BindAction(INPUT_BUTTON_5, IE_Released, this, &AControlledCharacterBase::Internal_Button_5_Released);

	// Left Trigger 2
	PlayerInputComponent->BindAction(INPUT_BUTTON_6 , IE_Pressed, this, &AControlledCharacterBase::Internal_Button_6_Pressed);
	PlayerInputComponent->BindAction(INPUT_BUTTON_6, IE_Released, this, &AControlledCharacterBase::Internal_Button_6_Released);

	// Right Trigger 1
	PlayerInputComponent->BindAction(INPUT_BUTTON_7 , IE_Pressed, this, &AControlledCharacterBase::Internal_Button_7_Pressed);
	PlayerInputComponent->BindAction(INPUT_BUTTON_7, IE_Released, this, &AControlledCharacterBase::Internal_Button_7_Released);

	// Right Trigger 2
	PlayerInputComponent->BindAction(INPUT_BUTTON_8 , IE_Pressed, this, &AControlledCharacterBase::Internal_Button_8_Pressed);
	PlayerInputComponent->BindAction(INPUT_BUTTON_8, IE_Released, this, &AControlledCharacterBase::Internal_Button_8_Released);
}

