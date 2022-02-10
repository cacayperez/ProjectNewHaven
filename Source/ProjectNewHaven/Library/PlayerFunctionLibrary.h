// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectNewHaven/Models/Settings/GameSetting.h"
#include "PlayerFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNEWHAVEN_API UPlayerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static bool IsPlayerPawn(APawn* Pawn);

	UFUNCTION(BlueprintCallable)
	static APawn* ValidatePlayerPawn(APawn* Pawn);
	
	UFUNCTION(BlueprintCallable)
	static AActor* Actor_IsSceneObject(AActor* Actor);
	
	UFUNCTION(BlueprintCallable)
	static AActor* GetObjectOnCursor(APlayerController* Controller);

	UFUNCTION(BlueprintCallable)
	static bool TraceCursorProjection(APlayerController* Controller, const ETraceTypeQuery Query, FVector& Location);

	UFUNCTION(BlueprintCallable)
	static bool TraceFloorViaCursor(APlayerController* Controller, FVector& FloorLocation);

	UFUNCTION(BlueprintCallable)
	static void SnapCursorToActor(APlayerController* Controller, AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static APawn* GetActivePawn(UObject* Context);

	UFUNCTION(BlueprintCallable)
	static EGameMode GetGameMode(UObject* Context);

};
