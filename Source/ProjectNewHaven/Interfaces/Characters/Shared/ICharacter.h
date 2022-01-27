// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNewHaven/Models/Character/CharacterModel.h"
#include "ProjectNewHaven/Models/Combat/DamageModel.h"
#include "UObject/Interface.h"
#include "ICharacter.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UICharacter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTNEWHAVEN_API IICharacter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetWalkSpeed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetRunSpeed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsRunning();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetCrouchSpeed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanMove();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TMap<ECharacterAnimation, UAnimMontage*> GetCharacterAnimationMap();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ECharacterMoveState GetCurrentMoveState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_FollowCharacter(ACharacter* Character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_ApproachActor(AActor* TargetActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_MoveToLocation(FVector Location);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Evade(FVector Direction);
	
	// World Related Interactions
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_OpenDoor(FVector Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_CloseDoor(FVector Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Interact(AActor* TargetActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Inspect(FVector Target);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_ReceiveDamage(AActor* Instigator, FDamageData DamageData);

	// UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	// void Action_Use_Equipment(EEquipmentSlot Slot);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Use_ItemInPocket_ViaSlot(int32 ItemSlot);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Use_ItemInPocket(FName ItemID);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Sit(FVector Target);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Run();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Walk();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Idle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Crouch();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Sleep();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_FaceActor(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_FaceDirection(FVector Direction);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Restrained();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Die();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action_Emote(ECharacterEmote EmoteType);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayAnimation(ECharacterAnimation Animation);
};
