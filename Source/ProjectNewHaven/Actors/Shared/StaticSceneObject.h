// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectNewHaven/Interfaces/Actors/Shared/ISceneObject.h"
#include "ProjectNewHaven/Player/PlayerControllerBase.h"
#include "StaticSceneObject.generated.h"

UCLASS()
class PROJECTNEWHAVEN_API AStaticSceneObject : public AActor, public IISceneObject
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh", meta = (AllowPrivateAccess = "true"))
	class UMeshComponent* MeshComponent;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsGrabbed = false;

	
public:
	// Sets default values for this actor's properties
	AStaticSceneObject();

protected:
	virtual void BeginPlay() override;

public:

	
	FORCEINLINE class UMeshComponent* GetMeshComponent() const { return MeshComponent; }
	
	virtual void OnSelect_Implementation() override;
	virtual void OnDeselect_Implementation() override;
	virtual void OnInspect_Implementation() override;
	virtual void OnInteract_Implementation() override;
	virtual bool IsGrabbed_Implementation() override;
	virtual void SetGrab_Implementation(bool bVal) override;
	UFUNCTION()
	void OnCursor_HoverIn(class UPrimitiveComponent * Component);

	UFUNCTION()
	void OnCursor_HoverOut(class UPrimitiveComponent * Component);

	UFUNCTION()
	void Interact_Mode_Adventure();
	
	UFUNCTION()
	void Interact_Mode_Build();
	
};

