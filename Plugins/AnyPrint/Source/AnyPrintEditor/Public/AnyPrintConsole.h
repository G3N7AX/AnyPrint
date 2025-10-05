// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "AnyPrintLibrary/Public/AnyPrintFunctionLibrary.h"
#include "AnyPrintWidget.h"
#include "AnyPrintConsole.generated.h"

class UScrollBox;
class UButton;
class UComboBoxKey;

/**
 * 
 */
UCLASS()
class ANYPRINTEDITOR_API UAnyPrintConsole : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	/* Public Variables */
	TArray<FLogInfo> LogEntries;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* LogScrollBox;

	UPROPERTY(meta = (BindWidget))
	UButton* ClearLogsButton;

	UPROPERTY(meta = (BindWidget))
	UComboBoxKey* FilterComboBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAnyPrintWidget> LogWidgetClass;

	/* Public Functions */
	void OnLogReceived(FLogInfo LogInfo);
	void CreateLogWidget(FLogInfo LogInfo);
	
	UFUNCTION()
	void OnClearLogs();
};
