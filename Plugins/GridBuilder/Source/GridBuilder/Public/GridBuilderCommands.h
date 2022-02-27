// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GridBuilderStyle.h"

class FGridBuilderCommands : public TCommands<FGridBuilderCommands>
{
public:

	FGridBuilderCommands()
		: TCommands<FGridBuilderCommands>(TEXT("GridBuilder"), NSLOCTEXT("Contexts", "GridBuilder", "GridBuilder Plugin"), NAME_None, FGridBuilderStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};