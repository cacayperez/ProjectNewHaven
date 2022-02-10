// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderFunctionLibrary.h"

#include "ProjectNewHaven/Debug/DebugHelper.h"

bool UBuilderFunctionLibrary::IsWall(UPrimitiveComponent* Component)
{
	const FName CollisionProfile = Component->GetCollisionProfileName();
	UDebugHelper::LOG(FString::Printf(TEXT("%s, %s"), *CollisionProfile.ToString(), *Component->GetName()));
	if(CollisionProfile == "Wall") return true;
	
	return false;
}
