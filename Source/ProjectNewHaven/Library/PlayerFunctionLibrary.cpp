// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectNewHaven/Config/GameplaySettings.h"
#include "ProjectNewHaven/Config/ViewportSettings.h"
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

void UPlayerFunctionLibrary::GetGridLocation(const FVector BaseLocation, FVector& GridLocation)
{
	const float GridSize = 25.0f;

	const FVector SnapLocation = FVector (
			FMath::CeilToFloat(BaseLocation.X / GridSize) * GridSize,
			FMath::CeilToFloat(BaseLocation.Y / GridSize) * GridSize,
			FMath::CeilToFloat(BaseLocation.Z / GridSize) * GridSize
		);
	
	GridLocation = SnapLocation;
	
}

bool UPlayerFunctionLibrary::TraceCursorProjection(APlayerController* Controller, const ETraceTypeQuery Query, FVector& Location)
{
	const bool bTrue = IsValid(Controller);
	if(!bTrue) return false;

	FHitResult HitResult;
	FVector2D MouseLocation;
	
	int32 ViewportSizeX, ViewportSizeY;
	Controller->GetViewportSize(ViewportSizeX, ViewportSizeY);
	Controller->GetMousePosition(MouseLocation.X, MouseLocation.Y);

	constexpr  float Top = VIEWPORT_CURSOR_PADDING;
	constexpr float Left = VIEWPORT_CURSOR_PADDING;
	const float Bottom = ViewportSizeY - VIEWPORT_CURSOR_PADDING;
	const float Right = ViewportSizeX - VIEWPORT_CURSOR_PADDING;
	
	bool bIsWithinViewport = true;

	if(MouseLocation.X < Left || MouseLocation.X > Right)
	{
		bIsWithinViewport = false;
	}
	
	if(MouseLocation.Y < Top || MouseLocation.Y > Bottom)
	{
		bIsWithinViewport = false;
	}

	if(!bIsWithinViewport)
	{
		MouseLocation.X = FMath::Clamp(MouseLocation.X, Left, Right);
		MouseLocation.Y = FMath::Clamp(MouseLocation.Y, Top, Bottom);
	}

	Controller->GetHitResultUnderCursorByChannel(Query, true, HitResult);
	
	FVector WorldDirection, WorldLocation;
	
	UGameplayStatics::DeprojectScreenToWorld(Controller, MouseLocation, WorldLocation, WorldDirection);
	WorldDirection = WorldDirection * HitResult.Distance;
	//Location = WorldLocation + WorldDirection;
	Location = HitResult.Location;
	// const float ZOffset = 2.5f;
	// Location.Z = Location.Z - ZOffset;
	
	return bIsWithinViewport;
}

bool UPlayerFunctionLibrary::TraceFloorViaCursor(APlayerController* Controller, FVector& FloorLocation)
{
	return TraceCursorProjection(Controller, UEngineTypes::ConvertToTraceType(ECC_FLoor), FloorLocation);
}



void UPlayerFunctionLibrary::SnapCursorToActor(APlayerController* Controller, AActor* Actor)
{
	if(Controller  == nullptr || Actor == nullptr) return;
	
	const FVector ActorLocation = Actor->GetActorLocation();
	FVector2D ScreenPosition;
	
	Controller->ProjectWorldLocationToScreen(ActorLocation, ScreenPosition);
	Controller->SetMouseLocation(ScreenPosition.X, ScreenPosition.Y);
}

APawn* UPlayerFunctionLibrary::GetActivePawn(UObject* Context)
{
	const APlayerController* Controller = UGameplayStatics::GetPlayerController(Context, 0);
	if(Controller != nullptr)
	{
		return Controller->GetPawn();
	}

	return nullptr;
}

EGameMode UPlayerFunctionLibrary::GetGameMode(UObject* Context)
{
	const APlayerController* Controller = UGameplayStatics::GetPlayerController(Context, 0);
	EGameMode Mode = EGameMode::None;
	if(Controller != nullptr)
	{
		const APlayerControllerBase* NHController = Cast<APlayerControllerBase>(Controller);

		if(IsValid(NHController))
		{
			Mode = NHController->GetGameMode();
		}
	}

	return Mode;
}
