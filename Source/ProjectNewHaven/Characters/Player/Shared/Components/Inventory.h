// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectNewHaven/Models/Actors/Shared/SceneObjectModel.h"
#include "Inventory.generated.h"


UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTNEWHAVEN_API UInventory : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<FSceneObjectData> Items;
	
public:
	// Sets default values for this component's properties
	UInventory();

};
