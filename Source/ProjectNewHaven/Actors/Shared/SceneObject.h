// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectNewHaven/Interfaces/Actors/Shared/ISceneObject.h"
#include "SceneObject.generated.h"

UCLASS(Abstract)
class PROJECTNEWHAVEN_API ASceneObject : public AActor , public IISceneObject
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* _RootComponent;

public:
	// Sets default values for this actor's properties
	ASceneObject();

};
