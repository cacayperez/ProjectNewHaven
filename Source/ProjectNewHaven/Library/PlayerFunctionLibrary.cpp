// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectNewHaven/Config/GameplaySettings.h"
#include "ProjectNewHaven/Config/ViewportSettings.h"
#include "ProjectNewHaven/Debug/DebugHelper.h"
#include "ProjectNewHaven/Interfaces/Actors/Shared/ISceneObject.h"
#include "ProjectNewHaven/Interfaces/Player/IPlayerPawn.h"
#include "ProjectNewHaven/Player/PlayerControllerBase.h"

bool UPlayerFunctionLibrary::IsPlayerPawn(APawn* Pawn)
{
	APawn* SubjectPawn = Pawn;
	bool bVal = false;

	if(SubjectPawn != nullptr && SubjectPawn->GetClass()->ImplementsInterface(UIPlayerPawn::StaticClass()) == true)
	{
		bVal = true;
	}

	return bVal;
}

APawn* UPlayerFunctionLibrary::ValidatePlayerPawn(APawn* Pawn)
{
	APawn* SubjectPawn = Pawn;

	if(SubjectPawn != nullptr && SubjectPawn->GetClass()->ImplementsInterface(UIPlayerPawn::StaticClass()) == true)
	{
		return SubjectPawn;
	}

	return nullptr;
}



AActor* UPlayerFunctionLibrary::GetObjectOnCursor(APlayerController* Controller)
{
	if(Controller == nullptr) return nullptr;

	FHitResult HitResult;
	const bool bHit = Controller->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_SceneObject), true, HitResult);

	if(bHit)
	{
		AActor* Actor = HitResult.GetActor();

		return Actor;
	}
	return nullptr;
}

bool UPlayerFunctionLibrary::Actor_IsSceneObject(const AActor* Actor)
{
	if(IsValid(Actor) && Actor->GetClass()->ImplementsInterface(UISceneObject::StaticClass()) == true)
	{
		return true;
	}

	return false;
}

void UPlayerFunctionLibrary::GetGridLocation(const FVector BaseLocation, FVector& GridLocation, const float ZOffset)
{
	constexpr float GridSize = 25.0f;
	GridLocation = FVector(
			FMath::CeilToFloat(BaseLocation.X / GridSize) * GridSize,
			FMath::CeilToFloat(BaseLocation.Y / GridSize) * GridSize,
			FMath::CeilToFloat(BaseLocation.Z / GridSize) * GridSize
		);
}

bool UPlayerFunctionLibrary::TraceCursorProjection(APlayerController* Controller, const ETraceTypeQuery Query, FVector& Location)
{
	if(!IsValid(Controller)) return false;

	FHitResult HitResult;

	int32 ViewportSizeX, ViewportSizeY;
	float MouseLocationX, MouseLocationY;
	
	Controller->GetViewportSize(ViewportSizeX, ViewportSizeY);
	Controller->GetMousePosition(MouseLocationX, MouseLocationY);

	constexpr float Top = VIEWPORT_CURSOR_PADDING;
	constexpr float Left = VIEWPORT_CURSOR_PADDING;
	const float Bottom = ViewportSizeY - VIEWPORT_CURSOR_PADDING;
	const float Right = ViewportSizeX - VIEWPORT_CURSOR_PADDING;

	const bool bIsWithinViewport =
		(
			(MouseLocationX < Left || MouseLocationX > Right) && 
			(MouseLocationY < Top || MouseLocationY > Bottom)
		) ? false : true;

	
	if(!bIsWithinViewport)
	{
		MouseLocationX = FMath::Clamp(MouseLocationX, Left, Right);
		MouseLocationY = FMath::Clamp(MouseLocationY, Top, Bottom);
	}

	const bool bHit = Controller->GetHitResultUnderCursorByChannel(Query, false, HitResult);

	Location = HitResult.Location;
	
	return (bIsWithinViewport && bHit);
}

bool UPlayerFunctionLibrary::TraceFloorViaCursor(APlayerController* Controller, FVector& FloorLocation)
{
	return TraceCursorProjection(Controller, UEngineTypes::ConvertToTraceType(ECC_FLoor), FloorLocation);
}



void UPlayerFunctionLibrary::SnapCursorToActor(APlayerController* Controller, AActor* Actor)
{
	if(Controller == nullptr || Actor == nullptr) return;

	const FVector ActorLocation = Actor->GetActorLocation();
	FVector2D ScreenPosition;

	Controller->ProjectWorldLocationToScreen(ActorLocation, ScreenPosition);
	Controller->SetMouseLocation(ScreenPosition.X, ScreenPosition.Y);
}

APawn* UPlayerFunctionLibrary::GetActivePawn(UObject* Context)
{
	const APlayerController* Controller = UGameplayStatics::GetPlayerController(Context, 0);
	if(IsValid(Controller))
	{
		return Controller->GetPawn();
	}

	return nullptr;
}

EGameMode UPlayerFunctionLibrary::GetGameMode(UObject* Context)
{
	const APlayerControllerBase* NHController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(Context, 0));

	if(IsValid(NHController))
	{
		return NHController->GetGameMode();
	}
	
	return EGameMode::None;
}

/*
 	// Early out if we clicked on a HUD hitbox
	if (GetHUD() != NULL && GetHUD()->GetHitBoxAtCoordinates(ScreenPosition, true))
	{
		return false;
	}

	FVector WorldOrigin;
	FVector WorldDirection;
	if (UGameplayStatics::DeprojectScreenToWorld(this, ScreenPosition, WorldOrigin, WorldDirection) == true)
	{
		return GetWorld()->LineTraceSingleByChannel(HitResult, WorldOrigin, WorldOrigin + WorldDirection * HitResultTraceDistance, TraceChannel, CollisionQueryParams);
	}

	return false;
 */
