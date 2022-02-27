// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

/**
 * 
 */
class GRIDBUILDER_API FGridEditorCustomization : public IDetailCustomization
{
public:
 virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
 static TSharedRef<IDetailCustomization> MakeInstance();
 static FReply ExecuteToolCommand(IDetailLayoutBuilder* DetailBuilder, UFunction* MethodToExecute);
};

