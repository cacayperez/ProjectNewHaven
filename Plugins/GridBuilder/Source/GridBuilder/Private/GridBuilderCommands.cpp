// Copyright Epic Games, Inc. All Rights Reserved.

#include "GridBuilderCommands.h"

#define LOCTEXT_NAMESPACE "FGridBuilderModule"

void FGridBuilderCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "GridBuilder", "Bring up GridBuilder window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
