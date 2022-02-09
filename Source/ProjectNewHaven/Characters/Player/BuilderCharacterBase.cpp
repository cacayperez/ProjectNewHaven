// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectNewHaven/Debug/DebugHelper.h"
#include "ProjectNewHaven/Interfaces/Actors/Shared/ISceneObject.h"
#include "ProjectNewHaven/Library/PlayerFunctionLibrary.h"
#include "ProjectNewHaven/Player/PlayerControllerBase.h"


// Sets default values
ABuilderCharacterBase::ABuilderCharacterBase()
{
	GetCapsuleComponent()->SetCollisionProfileName("Spectator");
	GetMesh()->SetCollisionProfileName("Spectator");
	
	
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
	FollowCamera->SetupAttachment(CameraBoom); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation


	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	GetCapsuleComponent()->SetSimulatePhysics( false );
	GetMesh()->SetSimulatePhysics(false);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
}

// Called every frame
void ABuilderCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsValid(GetPlayerControllerBase()) && IsValid(ActiveSceneObject))
	{
		TestDelta = TestDelta + DeltaTime; 
		FVector ActorLocation = ActiveSceneObject->GetActorLocation();
		FVector NewLocation;
		UPlayerFunctionLibrary::GetCursorLocation(GetPlayerControllerBase(), NewLocation);
		NewLocation.Z = GetActorLocation().Z;;

		FVector Interp = UKismetMathLibrary::VInterpTo(ActorLocation, NewLocation, TestDelta, 10.0f);
		
		ActiveSceneObject->SetActorLocation(Interp);
	}
}

APlayerControllerBase* ABuilderCharacterBase::GetPlayerControllerBase()
{
	{
		if(PlayerControllerBase == nullptr && Controller != nullptr)
		{
			PlayerControllerBase = Cast<APlayerControllerBase>(Controller);
		}

		return PlayerControllerBase;
	}
}


void ABuilderCharacterBase::PlayerAction_Move_Implementation(const float Value, const EAxis::Type Axis)
{
	if(Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(Axis);

		CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
		const FVector CameraLoc = CameraManager->GetCameraLocation();

		const FVector OldPosition = GetActorLocation();
		
		AddMovementInput( Direction, Value );

		//
		//
		// APlayerControllerBase* PController = Cast<APlayerControllerBase>(Controller);
		// if(IsValid(PController))
		// {
		// 	
		// 	float MouseX, MouseY;
		// 	FVector2D CameraLoc2D;
		// 	PController->GetMousePosition(MouseX, MouseY);
		// 	FVector Test = FMath::VInterpTo(OldPosition, GetActorLocation(), GetWorld()->GetDeltaSeconds(), 0.1f);
		// 	PController->ProjectWorldLocationToScreen(Test, CameraLoc2D, true);
		//
		// 	
		// 	
		// 	const float X = FMath::FInterpTo(MouseX, CameraLoc2D.X, GetWorld()->GetDeltaSeconds(), 0.1f);
		// 	const float Y = FMath::FInterpTo(MouseY, CameraLoc2D.Y, GetWorld()->GetDeltaSeconds(), 0.1f);
		// 	
		// 	PController->SetMouseLocation( X, Y);
		// }
	}
}

void ABuilderCharacterBase::PlayerAction_Interact_Implementation(AActor* Actor)
{
	if(Actor == nullptr) return;

	UDebugHelper::LOG(FString::Printf(TEXT("%s"), *Actor->GetName()));
	
	if(UPlayerFunctionLibrary::Actor_IsSceneObject(Actor) != nullptr)
	{
		
		IISceneObject::Execute_OnInteract(Actor);
		GrabSceneObject(Actor);
		
	}
}

void ABuilderCharacterBase::PlayerAction_Select_Implementation(AActor* Actor)
{
	if(UPlayerFunctionLibrary::Actor_IsSceneObject(Actor) != nullptr)
	{
		IISceneObject::Execute_OnSelect(Actor);
	}
}

void ABuilderCharacterBase::PlayerAction_Deselect_Implementation(AActor* Actor)
{
	if(UPlayerFunctionLibrary::Actor_IsSceneObject(Actor) != nullptr)
	{
		IISceneObject::Execute_OnDeselect(Actor);
	}
}

void ABuilderCharacterBase::Input_Axis_LeftStickX_Implementation(const float Rate)
{
	if(Rate != 0.0f)
	{
		Execute_PlayerAction_Move(this, Rate, EAxis::Y);
	}
}

void ABuilderCharacterBase::Input_Axis_LeftStickY_Implementation(const float Rate)
{
	if(Rate != 0.0f)
	{
		Execute_PlayerAction_Move(this, Rate, EAxis::X);
	}
}

void ABuilderCharacterBase::Input_Button_3_Pressed_Implementation()
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

void ABuilderCharacterBase::Input_Button_8_Pressed_Implementation()
{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;

}

void ABuilderCharacterBase::Input_Button_8_Released_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
}

void ABuilderCharacterBase::GrabSceneObject(AActor* Actor)
{
	IISceneObject::Execute_SetGrab(Actor, true);

	ActiveSceneObject = Actor;
	SetActorTickEnabled(true);
}
