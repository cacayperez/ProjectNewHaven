// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/BuilderInventory.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectNewHaven/Interfaces/Actors/Shared/ISceneObject.h"
#include "ProjectNewHaven/Library/PlayerFunctionLibrary.h"
#include "ProjectNewHaven/Player/PlayerControllerBase.h"


// Sets default values
ABuilderCharacterBase::ABuilderCharacterBase()
{
	Inventory = CreateDefaultSubobject<UBuilderInventory>(TEXT("Inventory"));
	GetMesh()->SetCollisionProfileName("Spectator");
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

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

	if(GetPlayerControllerBase() && IsValid(ActiveSceneObject))
	{
		SmoothSnapToCursor(ActiveSceneObject, DeltaTime);
	}
}

APlayerControllerBase* ABuilderCharacterBase::GetPlayerControllerBase()
{
	{
		if(PlayerControllerBase == nullptr &&  IsValid(Controller))
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
		
		AddMovementInput( Direction, Value );
	}
}

void ABuilderCharacterBase::PlayerAction_Interact_Implementation(AActor* Actor)
{
	const bool bIsValidSceneObject = UPlayerFunctionLibrary::Actor_IsSceneObject(Actor);

	if(bIsValidSceneObject)
	{
		if(ActiveSceneObject == nullptr)
		{
			GrabSceneObject(Actor);
		}
		else
		{
			PlaceActiveSceneObject();
		}

		IISceneObject::Execute_OnBuilderCharacter_Interact(Actor);
	}
}

void ABuilderCharacterBase::PlayerAction_Select_Implementation(AActor* Actor)
{
	// if(UPlayerFunctionLibrary::Actor_IsSceneObject(Actor))
	// {
	// 	IISceneObject::Execute_OnBuilderCharacter_Select(Actor);
	// }
}

void ABuilderCharacterBase::PlayerAction_Deselect_Implementation(AActor* Actor)
{
	// if(UPlayerFunctionLibrary::Actor_IsSceneObject(Actor))
	// {
	// 	IISceneObject::Execute_OnBuilderCharacter_Deselect(Actor);
	// }
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
			AActor* Actor = (ActiveSceneObject) ? ActiveSceneObject : UPlayerFunctionLibrary::GetObjectOnCursor(PlayerController);
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
	ActiveSceneObject = Actor;
	SetActorTickEnabled(true);
}

void ABuilderCharacterBase::PlaceActiveSceneObject()
{
	if(!IsValid(ActiveSceneObject)) return;
	
	SetActorTickEnabled(false);
	SmoothSnapToCursor(ActiveSceneObject);
	PreviousSceneObject = ActiveSceneObject;
	ActiveSceneObject = nullptr;
}

void ABuilderCharacterBase::SmoothSnapToCursor(AActor* Actor, const float DeltaTime)
{
	if(!IsValid(Actor)) return;
	
	FVector ActorLocation = Actor->GetActorLocation();
	FVector NewLocation;
	const bool bIsInViewportBounds = UPlayerFunctionLibrary::TraceFloorViaCursor(GetPlayerControllerBase(), NewLocation);
	NewLocation.Z = NewLocation.Z - 2.f;
	if(bIsInViewportBounds)
	{
		FVector SnapLocation;
		UPlayerFunctionLibrary::GetGridLocation(NewLocation, SnapLocation);
		//ActorLocation.Z = SnapLocation.Z;
		SnapLocation = (DeltaTime != 0.0f) ?
			FMath::VInterpTo(ActorLocation, SnapLocation, DeltaTime, 20.0f) :
			SnapLocation;

		
		Actor->SetActorLocation(SnapLocation);
	}
}
