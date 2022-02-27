// Fill out your copyright notice in the Description page of Project Settings.


#include "GridEditorCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "FGridBuilderModule"

void FGridEditorCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TSet<UClass*> Classes;
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder.GetObjectsBeingCustomized((ObjectsBeingCustomized));

	for(auto  WeakObject : ObjectsBeingCustomized)
	{
		if(UObject* Instance = WeakObject.Get())
		{
			Classes.Add(Instance->GetClass());
		}
	}

	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Commands");

	for(UClass* Class: Classes )
	{
		for(TFieldIterator<UFunction> FuncIt(Class); FuncIt; ++FuncIt)
		{
			UFunction* Function = *FuncIt;
			if(Function->HasAnyFunctionFlags(FUNC_Exec) && (Function->NumParms == 0))
			{
				const FString FunctionName = Function->GetName();
				const FText ButtonCaption = FText:: FromString(FunctionName);
				const FString FilterString = FunctionName;

				Category.AddCustomRow(ButtonCaption)
				.ValueContent()
				[
					SNew(SButton)
					.Text(ButtonCaption)
					.OnClicked(FOnClicked::CreateStatic(&FGridEditorCustomization::ExecuteToolCommand, &DetailBuilder, Function))];
			}
		}
	}
}

TSharedRef<IDetailCustomization> FGridEditorCustomization::MakeInstance()
{
	return MakeShareable(new FGridEditorCustomization);	
}

FReply FGridEditorCustomization::ExecuteToolCommand(IDetailLayoutBuilder* DetailBuilder, UFunction* MethodToExecute)
{
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder->GetObjectsBeingCustomized(ObjectsBeingCustomized);

	for(auto WeakObject : ObjectsBeingCustomized)
	{
		if(UObject* Instance = WeakObject.Get())
		{
			Instance->CallFunctionByNameWithArguments(*MethodToExecute->GetName(), *GLog, nullptr, true);
		}
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE