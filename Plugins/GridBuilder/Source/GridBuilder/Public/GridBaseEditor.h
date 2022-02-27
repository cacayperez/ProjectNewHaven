// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GridBaseEditor.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class GRIDBUILDER_API UGridBaseEditor : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FString Name;
};
