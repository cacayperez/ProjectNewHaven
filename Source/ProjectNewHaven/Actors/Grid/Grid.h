// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

UENUM()
enum class EGridMaterial
{
	None,
	Dirt,
	Stone,
	Water
};

USTRUCT()
struct FGridBlockData 
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	FIntVector GridPosition;

	UPROPERTY(VisibleAnywhere)
	EGridMaterial Material;
};

USTRUCT()
struct FGridData 
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	TArray<FGridBlockData> Blocks;
	
};
UCLASS()
class PROJECTNEWHAVEN_API AGrid : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* _RootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh", meta = (AllowPrivateAccess = "true"))
	class UInstancedStaticMeshComponent* InstancedGridMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh", meta = (AllowPrivateAccess = "true"))
	FIntVector GridDimensions;


	
	
public:
	// Sets default values for this actor's properties
	AGrid();

	FORCEINLINE class UInstancedStaticMeshComponent* GetGridMesh() const { return InstancedGridMesh; }
};