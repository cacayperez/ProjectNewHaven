// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectNewHaven/Player/PlayerControllerBase.h"

#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectNewHaven/Config/InputDefinitions.h"
#include "ProjectNewHaven/Config/ViewportSettings.h"
#include "ProjectNewHaven/Debug/DebugHelper.h"
#include "ProjectNewHaven/Interfaces/Player/IPlayerPawn.h"
#include "ProjectNewHaven/Library/PlayerFunctionLibrary.h"


APlayerControllerBase::APlayerControllerBase()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchEvents = false;

}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	// For Forward and Right Movement
	InputComponent->BindAxis(INPUT_AXIS_LEFT_Y, this, &APlayerControllerBase::Internal_Axis_LeftStickY);
	InputComponent->BindAxis(INPUT_AXIS_LEFT_X, this, &APlayerControllerBase::Internal_Axis_LeftStickX);

	// Axis Right
	// For Character Rotation
	InputComponent->BindAxis(INPUT_AXIS_RIGHT_Y, this, &APlayerControllerBase::Internal_Axis_RightStickY);
	InputComponent->BindAxis(INPUT_AXIS_RIGHT_X, this, &APlayerControllerBase::Internal_Axis_RightStickX);

	// Triangle
	InputComponent->BindAction(INPUT_BUTTON_1 , IE_Pressed, this, &APlayerControllerBase::Internal_Button_1_Pressed);
	InputComponent->BindAction(INPUT_BUTTON_1, IE_Released, this, &APlayerControllerBase::Internal_Button_1_Released);

	// Circle
	InputComponent->BindAction(INPUT_BUTTON_2 , IE_Pressed, this, &APlayerControllerBase::Internal_Button_2_Pressed);
	InputComponent->BindAction(INPUT_BUTTON_2, IE_Released, this, &APlayerControllerBase::Internal_Button_2_Released);

	// Square
	InputComponent->BindAction(INPUT_BUTTON_3 , IE_Pressed, this, &APlayerControllerBase::Internal_Button_3_Pressed);
	InputComponent->BindAction(INPUT_BUTTON_3, IE_Released, this, &APlayerControllerBase::Internal_Button_3_Released);

	// Cross
	InputComponent->BindAction(INPUT_BUTTON_4 , IE_Pressed, this, &APlayerControllerBase::Internal_Button_4_Pressed);

	InputComponent->BindAction(INPUT_BUTTON_4, IE_Released, this, &APlayerControllerBase::Internal_Button_4_Released);

	// Left Trigger 1
	InputComponent->BindAction(INPUT_BUTTON_5 , IE_Pressed, this, &APlayerControllerBase::Internal_Button_5_Pressed);
	InputComponent->BindAction(INPUT_BUTTON_5, IE_Released, this, &APlayerControllerBase::Internal_Button_5_Released);

	// Left Trigger 2
	InputComponent->BindAction(INPUT_BUTTON_6 , IE_Pressed, this, &APlayerControllerBase::Internal_Button_6_Pressed);
	InputComponent->BindAction(INPUT_BUTTON_6, IE_Released, this, &APlayerControllerBase::Internal_Button_6_Released);

	// Right Trigger 1
	InputComponent->BindAction(INPUT_BUTTON_7 , IE_Pressed, this, &APlayerControllerBase::Internal_Button_7_Pressed);
	InputComponent->BindAction(INPUT_BUTTON_7, IE_Released, this, &APlayerControllerBase::Internal_Button_7_Released);

	// Right Trigger 2
	InputComponent->BindAction(INPUT_BUTTON_8 , IE_Pressed, this, &APlayerControllerBase::Internal_Button_8_Pressed);
	InputComponent->BindAction(INPUT_BUTTON_8, IE_Released, this, &APlayerControllerBase::Internal_Button_8_Released);
}

void APlayerControllerBase::Internal_Button_1_Pressed()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_1_Pressed(ControlledPawn);	
	}
}

void APlayerControllerBase::Internal_Button_1_Released()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_1_Released(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_2_Pressed()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_2_Pressed(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_2_Released()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_2_Released(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_3_Pressed()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_3_Pressed(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_3_Released()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_3_Released(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_4_Pressed()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_4_Pressed(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_4_Released()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_4_Released(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_5_Pressed()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_5_Pressed(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_5_Released()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_5_Released(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_6_Pressed()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_6_Pressed(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_6_Released()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_6_Released(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_7_Pressed()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_7_Pressed(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_7_Released()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_7_Released(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Button_8_Pressed()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_8_Pressed(ControlledPawn);
	}
	
}

void APlayerControllerBase::Internal_Button_8_Released()
{
	if(ControlledPawn != nullptr)
	{
		IIPlayerPawn::Execute_Input_Button_8_Released(ControlledPawn);
	}
}

void APlayerControllerBase::Internal_Axis_RightStickX(const float Rate)
{
	MoveCursor_Gamepad(Rate, EAxis::Y);
}

void APlayerControllerBase::Internal_Axis_RightStickY(const float Rate)
{
	MoveCursor_Gamepad(Rate, EAxis::X);
}

void APlayerControllerBase::Internal_Axis_LeftStickX(const float Rate)
{
	
	if(ControlledPawn != nullptr && Rate != 0.0f)
	{
		IIPlayerPawn::Execute_Input_Axis_LeftStickX(ControlledPawn, Rate);
		
	}
}

void APlayerControllerBase::Internal_Axis_LeftStickY(const float Rate)
{
	if(ControlledPawn != nullptr && Rate != 0.0f)
	{
		IIPlayerPawn::Execute_Input_Axis_LeftStickY(ControlledPawn, Rate);
		
	}
}

void APlayerControllerBase::Internal_Axis_MouseX(const float Rate)
{
	MoveCursor(Rate, EAxis::Y);
	
}

void APlayerControllerBase::Internal_Axis_MouseY(const float Rate)
{
	MoveCursor(Rate, EAxis::X);
}

void APlayerControllerBase::MoveCursor_Gamepad(const float Rate, const EAxis::Type Axis)
{
	if(Rate == 0.0f) return;
	
	float MousePositionX, MousePositionY;
	int32 ViewportSizeX, ViewportSizeY;
	
	GetMousePosition(MousePositionX, MousePositionY);

	float X = MousePositionX;
	float Y = MousePositionY;
	const float Delta = GetWorld()->GetDeltaSeconds();
	
	const float Speed =  Rate *  (BaseCursorSpeed/ Delta);

	if(Axis == EAxis::X)
	{
		Y = MousePositionY + Speed;
	}

	if(Axis == EAxis::Y)
	{
		X = MousePositionX + Speed;
	}

	
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	const float InterpX = FMath::FInterpTo(MousePositionX, X, Delta, 30.f);
	const float InterpY = FMath::FInterpTo(MousePositionY, Y, Delta, 30.f);
	
	const int32 NewPositionX = UKismetMathLibrary::Clamp(InterpX, VIEWPORT_CURSOR_PADDING, ViewportSizeX - VIEWPORT_CURSOR_PADDING);
	const int32 NewPositionY = UKismetMathLibrary::Clamp(InterpY, VIEWPORT_CURSOR_PADDING, ViewportSizeY - VIEWPORT_CURSOR_PADDING);

	SetMouseLocation(NewPositionX, NewPositionY);
}

void APlayerControllerBase::MoveCursor(const float Rate, const EAxis::Type Axis)
{
	if(Rate == 0.0f) return;

	const float Clamped_Rate = FMath::Clamp(Rate, -1.0f, 1.0f);
	
	float MousePositionX, MousePositionY;
	int32 ViewportSizeX, ViewportSizeY;
	
	GetMousePosition(MousePositionX, MousePositionY);

	float X = MousePositionX;
	float Y = MousePositionY;
	const float Delta = GetWorld()->GetDeltaSeconds();
	
	const float Speed =  Clamped_Rate *  (BaseCursorSpeed/ Delta);

	if(Axis == EAxis::X)
	{
		Y = MousePositionY - Speed;
	}

	if(Axis == EAxis::Y)
	{
		X = MousePositionX + Speed;
	}

	
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	const float InterpX = FMath::FInterpTo(MousePositionX, X, Delta, 30.f);
	const float InterpY = FMath::FInterpTo(MousePositionY, Y, Delta, 30.f);

	
	
	const int32 NewPositionX = UKismetMathLibrary::Clamp(InterpX, VIEWPORT_CURSOR_PADDING, ViewportSizeX - VIEWPORT_CURSOR_PADDING);
	const int32 NewPositionY = UKismetMathLibrary::Clamp(InterpY, VIEWPORT_CURSOR_PADDING, ViewportSizeY - VIEWPORT_CURSOR_PADDING);

	SetMouseLocation(NewPositionX, NewPositionY);
}

void APlayerControllerBase::SetPawn(APawn* InPawn)
{
	//const bool bIsPlayerPawn =  UPlayerFunctionLibrary::IsPlayerPawn(InPawn);
	APawn* SubjectPawn = UPlayerFunctionLibrary::ValidatePlayerPawn(InPawn);
	if(IsValid(SubjectPawn))
	{
		ControlledPawn = InPawn;
	}
	
	Super::SetPawn(InPawn);
}

void APlayerControllerBase::StopCursor()
{
	float X, Y;
	GetMousePosition(X, Y);
	SetMouseLocation(X, Y);
}
