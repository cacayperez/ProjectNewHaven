// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneObject.h"


// Sets default values
ASceneObject::ASceneObject()
{
	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _RootComponent;
}
