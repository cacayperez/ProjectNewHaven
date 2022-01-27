// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimationAssistLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNEWHAVEN_API UAnimationAssistLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void PlayMontage(class USkeletalMeshComponent* SkeletalMeshComponent, class UAnimMontage* AnimMontage, const bool bOverrideAnim = false);
};
