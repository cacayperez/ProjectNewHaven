// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticSceneObject.h"

#include "Components/BoxComponent.h"
#include "GameFramework/MovementComponent.h"
#include "ProjectNewHaven/Debug/DebugHelper.h"
#include "ProjectNewHaven/Library/PlayerFunctionLibrary.h"


// Sets default values
AStaticSceneObject::AStaticSceneObject()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionProfileName(FName("SceneObject"));
	
}


void AStaticSceneObject::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnBeginCursorOver.AddDynamic(this, &AStaticSceneObject::OnCursor_HoverIn);
	MeshComponent->OnEndCursorOver.AddDynamic(this, &AStaticSceneObject::OnCursor_HoverOut);
}




void AStaticSceneObject::OnSelect_Implementation()
{
	GetMeshComponent()->SetRenderCustomDepth(true);
}

void AStaticSceneObject::OnDeselect_Implementation()
{
	GetMeshComponent()->SetRenderCustomDepth(false);
}

void AStaticSceneObject::OnInspect_Implementation()
{
	// To-do
	
}

void AStaticSceneObject::OnInteract_Implementation()
{
	const EGameMode Mode = UPlayerFunctionLibrary::GetGameMode(this);

	switch (Mode)
	{
	case EGameMode::None: break;
	case EGameMode::Adventure:
		Interact_Mode_Adventure();
		break;
	case EGameMode::Build:
		Interact_Mode_Build();
		break;
	default: ;
	}
}

bool AStaticSceneObject::IsGrabbed_Implementation()
{
	return bIsGrabbed;
}

void AStaticSceneObject::SetGrab_Implementation(bool bVal)
{
	bIsGrabbed = bVal;
}

void AStaticSceneObject::OnCursor_HoverIn(UPrimitiveComponent * Component)
{
	Execute_OnSelect(this);
}

void AStaticSceneObject::OnCursor_HoverOut(UPrimitiveComponent* Component)
{
	
}

void AStaticSceneObject::Interact_Mode_Adventure()
{
	
}

void AStaticSceneObject::Interact_Mode_Build()
{

}

