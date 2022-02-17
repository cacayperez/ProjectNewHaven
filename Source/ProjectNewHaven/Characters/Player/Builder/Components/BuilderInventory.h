// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectNewHaven/Characters/Player/Shared/Components/Inventory.h"
#include "BuilderInventory.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTNEWHAVEN_API UBuilderInventory : public UInventory
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBuilderInventory();

};
