// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GridBaseEditor.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FGridBuilderModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	//void PluginButtonClicked();

	static void CreateToolListMenu(class FMenuBuilder& MenuBuilder);
	static void TriggerTool(UClass* ToolClass);
	static void OnToolWindowClosed(const TSharedRef<SWindow>& Window, UGridBaseEditor* Instance);
private:

	void RegisterMenus();

	//TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);


private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
