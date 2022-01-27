// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationAssistLibrary.h"

void UAnimationAssistLibrary::PlayMontage(USkeletalMeshComponent* SkeletalMeshComponent, UAnimMontage* AnimMontage, const bool bOverrideAnim)
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();

	if(!bOverrideAnim && !AnimInstance->IsAnyMontagePlaying())
	{
		AnimInstance->Montage_Play(AnimMontage);
	}
	
}
