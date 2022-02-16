// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectNewHaven/Interfaces/Actors/Shared/ISceneObject.h"
#include "ProjectNewHaven/Library/PlayerFunctionLibrary.h"
#include "ProjectNewHaven/Player/PlayerControllerBase.h"


// Sets default values
ABuilderCharacterBase::ABuilderCharacterBase()
{
	//GetCapsuleComponent()->SetCollisionProfileName("Spectator");
	GetMesh()->SetCollisionProfileName("Spectator");
	
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1000.f;
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
		SmoothSnapToCursor(ActiveSceneObject, DeltaTime);
		// const FVector ActorLocation = ActiveSceneObject->GetActorLocation();
		// FVector NewLocation;
		// const bool bIsInViewportBounds = UPlayerFunctionLibrary::TraceFloorViaCursor(GetPlayerControllerBase(), NewLocation);
		//
		// if(bIsInViewportBounds)
		// {
		// 	const float GridSize = 50.0f;
		// 	const float SnapX = FMath::CeilToFloat(NewLocation.X / GridSize) * GridSize;
		// 	const float SnapY = FMath::CeilToFloat(NewLocation.Y / GridSize) * GridSize;
		// 	const float SnapZ = FMath::CeilToFloat(NewLocation.Z / GridSize) * GridSize;
		//
		// 	FVector SnapLocation;
		// 	NewLocation.Z = ActorLocation.Z;
		// 	UPlayerFunctionLibrary::GetGridLocation(NewLocation, SnapLocation);
		//
		// 	
		// 	
		// 	const FVector SmoothedLocation = UKismetMathLibrary::VInterpTo(ActorLocation, SnapLocation, DeltaTime, 20.0f);
		// 	//const FVector SmoothedLocation = UKismetMathLibrary::VInterpTo(ActorLocation, NewLocation, DeltaTime, 20.0f);
		//
		// 	ActiveSceneObject->SetActorLocation(SmoothedLocation);
		// }
		
		
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
		
		AddMovementInput( Direction, Value );
	}
}

void ABuilderCharacterBase::PlayerAction_Interact_Implementation(AActor* Actor)
{

	if(ActiveSceneObject == nullptr)
	{
		const bool bIsValidSceneObject = UPlayerFunctionLibrary::Actor_IsSceneObject(Actor);
		if(bIsValidSceneObject)
		{
			IISceneObject::Execute_OnBuilderCharacter_Interact(Actor);
			UPlayerFunctionLibrary::SnapCursorToActor(Cast<APlayerController>(Controller), Actor);
			GrabSceneObject(Actor);
		
		}
	}
	else
	{
		PlaceActiveSceneObject();
	}
}

void ABuilderCharacterBase::PlayerAction_Select_Implementation(AActor* Actor)
{
	if(UPlayerFunctionLibrary::Actor_IsSceneObject(Actor))
	{
		IISceneObject::Execute_OnBuilderCharacter_Select(Actor);
	}
}

void ABuilderCharacterBase::PlayerAction_Deselect_Implementation(AActor* Actor)
{
	if(UPlayerFunctionLibrary::Actor_IsSceneObject(Actor))
	{
		IISceneObject::Execute_OnBuilderCharacter_Deselect(Actor);
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

void ABuilderCharacterBase::PlaceActiveSceneObject()
{
	if(ActiveSceneObject == nullptr) return;
	
	
	SetActorTickEnabled(false);
	SmoothSnapToCursor(ActiveSceneObject);
	PreviousSceneObject = ActiveSceneObject;
	ActiveSceneObject = nullptr;

	
}

void ABuilderCharacterBase::SmoothSnapToCursor(AActor* Actor, const float DeltaTime)
{
	const bool bTrue = IsValid(Actor);
	if(!bTrue) return;
	
	const FVector ActorLocation = Actor->GetActorLocation();
	FVector NewLocation;
	const bool bIsInViewportBounds = UPlayerFunctionLibrary::TraceFloorViaCursor(GetPlayerControllerBase(), NewLocation);

	
	if(bIsInViewportBounds)
	{
		FVector SnapLocation;
		NewLocation.Z = ActorLocation.Z;
		UPlayerFunctionLibrary::GetGridLocation(NewLocation, SnapLocation);

		if(DeltaTime != 0.0f)
		{
			const FVector SmoothedLocation = UKismetMathLibrary::VInterpTo(ActorLocation, SnapLocation, DeltaTime, 20.0f);
			Actor->SetActorLocation(SmoothedLocation);
		}
		else
		{
			Actor->SetActorLocation(SnapLocation);
		}
		
	}
		
}
