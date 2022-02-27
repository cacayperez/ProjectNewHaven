// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

#include "ProjectNewHaven/Debug/DebugHelper.h"

// Sets default values
AGrid::AGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = _RootComponent;

	InstancedGridMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMesh"));
	InstancedGridMesh->SetupAttachment(InstancedGridMesh);
	
}

