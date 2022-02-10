// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticSceneObject.h"

#include "Components/BoxComponent.h"
#include "GameFramework/MovementComponent.h"
#include "ProjectNewHaven/Debug/DebugHelper.h"
#include "ProjectNewHaven/Library/BuilderFunctionLibrary.h"
#include "ProjectNewHaven/Library/PlayerFunctionLibrary.h"


// Sets default values
AStaticSceneObject::AStaticSceneObject()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Base = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	
	RootComponent = Base;
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionProfileName(FName("SceneObject"));
}


void AStaticSceneObject::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnBeginCursorOver.AddDynamic(this, &AStaticSceneObject::OnCursor_HoverIn);
	
	MeshComponent->OnEndCursorOver.AddDynamic(this, &AStaticSceneObject::OnCursor_HoverOut);

}

FVector AStaticSceneObject::GetBaseLocation_Implementation() const
{
	return Base->GetComponentLocation();
}

void AStaticSceneObject::OnBuilderCharacter_Select_Implementation()
{
	GetMeshComponent()->SetRenderCustomDepth(true);
}

void AStaticSceneObject::OnBuilderCharacter_Deselect_Implementation()
{
	GetMeshComponent()->SetRenderCustomDepth(false);

}

void AStaticSceneObject::OnBuilderCharacter_Inspect_Implementation()
{
	
}

void AStaticSceneObject::OnBuilderCharacter_Interact_Implementation()
{

}

bool AStaticSceneObject::HasCollided_Implementation()
{
	return bHasCollided;
}

bool AStaticSceneObject::IsGrabbed_Implementation()
{
	return bIsGrabbed;
}

void AStaticSceneObject::SetGrab_Implementation(bool bVal)
{
	bIsGrabbed = bVal;

}

/*void AStaticSceneObject::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UDebugHelper::LOG(TEXT("HELLOO"));
	//bHasCollided = UBuilderFunctionLibrary::IsWall(OtherComp);

	
}

void AStaticSceneObject::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bHasCollided = false;
}*/

void AStaticSceneObject::OnCursor_HoverIn(UPrimitiveComponent * Component)
{
	Execute_OnBuilderCharacter_Select(this);
}

void AStaticSceneObject::OnCursor_HoverOut(UPrimitiveComponent* Component)
{
	
}


