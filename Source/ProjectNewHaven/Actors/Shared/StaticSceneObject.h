// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneObject.h"
#include "GameFramework/Actor.h"
#include "ProjectNewHaven/Interfaces/Actors/Shared/ISceneObject.h"
#include "ProjectNewHaven/Player/PlayerControllerBase.h"
#include "StaticSceneObject.generated.h"

UCLASS()
class PROJECTNEWHAVEN_API AStaticSceneObject : public ASceneObject
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh", meta = (AllowPrivateAccess = "true"))
	class UMeshComponent* MeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsGrabbed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bHasCollided = false;
	
public:
	// Sets default values for this actor's properties
	AStaticSceneObject();

protected:
	virtual void BeginPlay() override;

public:
	// virtual FVector GetBaseLocation_Implementation() const override;
	FORCEINLINE class UMeshComponent* GetMeshComponent() const { return MeshComponent; }

	virtual void OnBuilderCharacter_Select_Implementation() override;
	virtual void OnBuilderCharacter_Deselect_Implementation() override;
	virtual void OnBuilderCharacter_Inspect_Implementation() override;
	virtual void OnBuilderCharacter_Interact_Implementation() override;
	virtual bool HasCollided_Implementation() override;
	virtual bool IsMountable_Implementation() override;

	virtual bool IsGrabbed_Implementation() override;
	virtual void SetGrab_Implementation(bool bVal) override;
	
	UFUNCTION()
	void OnCursor_HoverIn(class UPrimitiveComponent * Component);

	UFUNCTION()
	void OnCursor_HoverOut(class UPrimitiveComponent * Component);

};

