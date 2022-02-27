// Copyright Epic Games, Inc. All Rights Reserved.

#include "GridBuilder.h"

#include "GridBaseEditor.h"
#include "GridBuilderStyle.h"
#include "GridBuilderCommands.h"
#include "GridEditorCustomization.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName GridBuilderTabName("GridBuilder");

#define LOCTEXT_NAMESPACE "FGridBuilderModule"

void FGridBuilderModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.RegisterCustomClassLayout("GridBaseEditor", FOnGetDetailCustomizationInstance::CreateStatic(FGridEditorCustomization::MakeInstance));

		PropertyModule.NotifyCustomizationModuleChanged();
	}
	
	FGridBuilderStyle::Initialize();
	FGridBuilderStyle::ReloadTextures();

	FGridBuilderCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	// PluginCommands->MapAction(
	// 	FGridBuilderCommands::Get().OpenPluginWindow,
	// 	FExecuteAction::CreateRaw(this, &FGridBuilderModule::PluginButtonClicked),
	// 	FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGridBuilderModule::RegisterMenus));

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	struct Local
	{
		static void AddToolbarCommands(FToolBarBuilder& ToolBarBuilder)
		{
			//ToolBarBuilder.AddToolBarButton(FGridBuilderCommands::Get().TestCommand);
		}

		static void AddMenuCommands(FMenuBuilder& MenuBuilder)
		{
			MenuBuilder.AddSubMenu(LOCTEXT("FGridBuilderTabTitle", "GridBuilder"),
				LOCTEXT("FGridBuilderTabTitle", "GridBuilder"),
				FNewMenuDelegate::CreateStatic(&FGridBuilderModule::CreateToolListMenu)
				);
			
		}
	};
	
	TSharedRef<FExtender> MenuExtender(new FExtender());
	MenuExtender->AddMenuExtension(
		"EditMain",
		EExtensionHook::After,
		PluginCommands.ToSharedRef(),
		FMenuExtensionDelegate::CreateStatic(&Local::AddMenuCommands));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	

}

void FGridBuilderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FGridBuilderStyle::Shutdown();
	FGridBuilderCommands::Unregister();
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(GridBuilderTabName);
}



// void FGridBuilderModule::PluginButtonClicked()
// {
// 	FGlobalTabmanager::Get()->TryInvokeTab(GridBuilderTabName);
// }

void FGridBuilderModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FGridBuilderCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FGridBuilderCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

// TSharedRef<SDockTab> FGridBuilderModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
// {
// 	//FUIAction(FExecuteAction::CreateStatic(&FGridBuilderModule::Tr))
// }

void FGridBuilderModule::CreateToolListMenu(FMenuBuilder& MenuBuilder)
{
	for(TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		UClass* Class = *ClassIt;
		if(!Class->HasAnyClassFlags(CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_Abstract))
		{
			if(Class->IsChildOf(UGridBaseEditor::StaticClass()))
			{
				FString FriendlyName = Class->GetName();
				FText MenuDescription = FText::Format(LOCTEXT("ToolMenuDescription", "{0}"), FText::FromString(FriendlyName));
				FText MenuTooltip = FText::Format(LOCTEXT("ToolMenuTooltip", "Execute the {0} tool"), FText::FromString(FriendlyName));

				FUIAction Action(FExecuteAction::CreateStatic(&FGridBuilderModule::TriggerTool, Class));

				MenuBuilder.AddMenuEntry(
					MenuDescription,
					MenuTooltip,
					FSlateIcon(),
					Action);
			}
		}
	}
}

void FGridBuilderModule::TriggerTool(UClass* ToolClass)
{
	UGridBaseEditor* ToolInstance = NewObject<UGridBaseEditor>(GetTransientPackage(), ToolClass);
	ToolInstance->AddToRoot();

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	TArray<UObject*> ObjectsToView;
	ObjectsToView.Add(ToolInstance);
	TSharedRef<SWindow> Window = PropertyEditorModule.CreateFloatingDetailsView(ObjectsToView, false);
	Window->SetOnWindowClosed(FOnWindowClosed::CreateStatic(FGridBuilderModule::OnToolWindowClosed, ToolInstance));
}

void FGridBuilderModule::OnToolWindowClosed(const TSharedRef<SWindow>& Window, UGridBaseEditor* Instance)
{
	Instance->RemoveFromRoot();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGridBuilderModule, GridBuilder)