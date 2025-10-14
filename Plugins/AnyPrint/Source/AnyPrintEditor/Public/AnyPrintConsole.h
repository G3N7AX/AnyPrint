// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "AnyPrintConsole.generated.h"

class UWidgetSwitcher;
class UButton;
class UTextBlock;

/**
 * 
 */

UCLASS()
class ANYPRINTEDITOR_API UAnyPrintConsole : public UEditorUtilityWidget
{
	GENERATED_BODY()


public:
	
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* PanelSwitcher;

	UPROPERTY(meta = (BindWidget))
	UButton* ConsoleButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ConsoleButtonText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SettingsButtonText;

	UFUNCTION()
	void ShowIndexZero();

	UFUNCTION()
	void ShowIndexOne();
};
