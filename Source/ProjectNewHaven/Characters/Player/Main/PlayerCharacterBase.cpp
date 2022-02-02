// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ProjectNewHaven/Config/InputDefinitions.h"
#include "ProjectNewHaven/Debug/DebugHelper.h"
#include "ProjectNewHaven/Library/AnimationAssistLibrary.h"

// Sets default values
APlayerCharacterBase::APlayerCharacterBase()
{
	CurrentMoveState = ECharacterMoveState::None;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->JumpZVelocity = 600.f;
	
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent_Interaction"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetRelativeLocation(FVector(30.0f, 0.0f , 0.0f));
	InteractionBox->SetBoxExtent(FVector(64.0f, 40.0f, 90.0f));

	Execute_Action_Walk(this);
}


void APlayerCharacterBase::Input_Axis_LeftStickX_Implementation(const float Rate)
{
	if(Rate != 0.0f)
	{
		Execute_PlayerAction_Move(this, Rate, EAxis::Y);
	}
	
}

void APlayerCharacterBase::Input_Axis_LeftStickY_Implementation(const float Rate)
{
	if(Rate != 0.0f)
	{
		Execute_PlayerAction_Move(this, Rate, EAxis::X);
	}
}



ECharacterMoveState APlayerCharacterBase::GetCurrentMoveState_Implementation()
{
	return IICharacter::GetCurrentMoveState_Implementation();
}

float APlayerCharacterBase::GetWalkSpeed_Implementation()
{
	return WalkSpeed;
}

float APlayerCharacterBase::GetRunSpeed_Implementation()
{
	return RunSpeed;
}

float APlayerCharacterBase::GetCrouchSpeed_Implementation()
{
	return CrouchSpeed;
}

bool APlayerCharacterBase::CanMove_Implementation()
{
	if(CurrentMoveState == ECharacterMoveState::Restrained)
	{
		return false;
	}

	if(CurrentMoveState == ECharacterMoveState::Evading)
	{
		return false;
	}
	
	return true;
}

bool APlayerCharacterBase::IsRunning_Implementation()
{
	if(CurrentMoveState == ECharacterMoveState::Running)
	{
		return true;
	}

	return false;
}

void APlayerCharacterBase::Action_Run_Implementation()
{
	if(Execute_CanMove(this))
	{
		UDebugHelper::LOG(TEXT("RUN"));
		CurrentMoveState = ECharacterMoveState::Running;
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		
	}
}

void APlayerCharacterBase::Action_Walk_Implementation()
{
	if(Execute_CanMove(this))
	{
		CurrentMoveState = ECharacterMoveState::Walking;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void APlayerCharacterBase::Action_Crouch_Implementation()
{
	if(Execute_CanMove(this))
	{

		if(!bIsCrouched)
		{
			Crouch();
			CurrentMoveState = ECharacterMoveState::Crouching;
		}
		else
		{
			UnCrouch();
			CurrentMoveState = ECharacterMoveState::None;
		}
		
	}
}

void APlayerCharacterBase::Action_Evade_Implementation(FVector Direction)
{
	UAnimMontage* Montage = CharacterAnimationMap.FindRef(ECharacterAnimation::DodgeRoll);
	if(Montage != nullptr)
	{
		UAnimationAssistLibrary::PlayMontage(GetMesh(), Montage);
	}
}

void APlayerCharacterBase::PlayerAction_Move_Implementation(const float Value, const EAxis::Type Axis)
{
	const bool bCanMove = Execute_CanMove(this);
	if(Controller != nullptr && bCanMove)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Direction
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(Axis);

		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacterBase::Input_Button_1_Pressed_Implementation()
{
	
}

void APlayerCharacterBase::Input_Button_4_Pressed_Implementation()
{
	Execute_Action_Evade(this, FVector(.0f, .0f, .0f));
}

void APlayerCharacterBase::Input_Button_6_Pressed_Implementation()
{
	
	Execute_Action_Crouch(this);
}

void APlayerCharacterBase::Input_Button_8_Pressed_Implementation()
{
	Execute_Action_Run(this);
}

void APlayerCharacterBase::Input_Button_8_Released_Implementation()
{
	Execute_Action_Walk(this);
}





