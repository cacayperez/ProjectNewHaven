// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldBuilderBase.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectNewHaven/Debug/DebugHelper.h"
#include "ProjectNewHaven/Interfaces/Actors/Shared/ISceneObject.h"
#include "ProjectNewHaven/Library/PlayerFunctionLibrary.h"



// Sets default values
AWorldBuilderBase::AWorldBuilderBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	bAddDefaultMovementBindings = false;
	// GetMeshComponent()->SetCollisionProfileName("NoCollision");
	GetCollisionComponent()->SetCollisionProfileName("NoCollision");

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;
	// CameraBoom->bEnableCameraLag = true;
	// CameraBoom->CameraLagMaxDistance = 30.0f;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->PostProcessSettings.bOverride_MotionBlurAmount = true;
	FollowCamera->PostProcessSettings.MotionBlurAmount = 0;
	FollowCamera->PostProcessSettings.MotionBlurMax = 0;

	FloatingPawnMovement = Cast<UFloatingPawnMovement>(ADefaultPawn::GetMovementComponent());

	if(FloatingPawnMovement != nullptr)
	{
		FloatingPawnMovement->MaxSpeed = DefaultSpeed;
		// FloatingPawnMovement->Acceleration = 400.0f;
		// FloatingPawnMovement->Deceleration = 400.0f;
	}

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AWorldBuilderBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsValid(GetPlayerControllerBase()) && IsValid(ActiveSceneObject))
	{
		FVector ActorLocation = ActiveSceneObject->GetActorLocation();
		FVector NewLocation;
		UPlayerFunctionLibrary::GetCursorLocation(GetPlayerControllerBase(), NewLocation);
		NewLocation.Z = GetActorLocation().Z;

		FVector Interp = FMath::VInterpTo(ActorLocation, NewLocation, DeltaSeconds, 0.1f);
		ActiveSceneObject->SetActorLocation(Interp);
	}
}

void AWorldBuilderBase::PlayerAction_Move_Implementation(const float Value, const EAxis::Type Axis)
{
	if(Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(Axis);

		const float NewVal = Value * GetWorld()->GetDeltaSeconds();
		AddMovementInput( Direction, NewVal );
	}
}

void AWorldBuilderBase::PlayerAction_Interact_Implementation(AActor* Actor)
{
	if(Actor == nullptr) return;

	UDebugHelper::LOG(FString::Printf(TEXT("%s"), *Actor->GetName()));
	
	if(UPlayerFunctionLibrary::Actor_IsSceneObject(Actor) != nullptr)
	{
		
		IISceneObject::Execute_OnInteract(Actor);
		GrabSceneObject(Actor);
		
	}
}

void AWorldBuilderBase::PlayerAction_Select_Implementation(AActor* Actor)
{
	if(UPlayerFunctionLibrary::Actor_IsSceneObject(Actor) != nullptr)
	{
		IISceneObject::Execute_OnSelect(Actor);
	}
}

void AWorldBuilderBase::PlayerAction_Deselect_Implementation(AActor* Actor)
{
	if(UPlayerFunctionLibrary::Actor_IsSceneObject(Actor) != nullptr)
	{
		IISceneObject::Execute_OnDeselect(Actor);
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

void AWorldBuilderBase::Input_Button_3_Pressed_Implementation()
{
	if(Controller != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Controller);

		if(IsValid(PlayerController))
		{
			AActor* Actor = UPlayerFunctionLibrary::GetObjectOnCursor(PlayerController);
			Execute_PlayerAction_Interact(this, Actor);
		}
		
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

void AWorldBuilderBase::GrabSceneObject(AActor* Actor)
{
	IISceneObject::Execute_SetGrab(Actor, true);

	ActiveSceneObject = Actor;
	SetActorTickEnabled(true);
}


