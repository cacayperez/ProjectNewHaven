// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DebugHelper.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNEWHAVEN_API UDebugHelper : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE static void LOG(const FString &Message, const float &TimeToDisplay = 2.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, FColor::Green, Message);
	}

	FORCEINLINE static void LOG_WARN(const FString &Message, const float &TimeToDisplay = 2.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, FColor::Yellow, Message);
	}

	FORCEINLINE static void LOG_ERROR(const FString &Message, const float &TimeToDisplay = 2.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, FColor::Red, Message);
	}
};
