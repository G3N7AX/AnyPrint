// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnyPrintLog.h"
#include "AnyPrintManager.generated.h"

class UScrollBox;
class UButton;
class UTextBlock;
class UComboBoxKey;

struct FSlateFontInfo;

/**
 * 
 */

UCLASS()
class ANYPRINTEDITOR_API UAnyPrintManager : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;

	UPROPERTY()
	TArray<UAnyPrintLog*> LogEntries;

	FSlateFontInfo LogFontInfo;
	FSlateFontInfo DetailsFontInfo;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* LogScrollBox;

	UPROPERTY(meta = (BindWidget))
	UButton* ClearButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ClearButtonText;

	UPROPERTY(meta = (BindWidgetOptional))
	UComboBoxKey* FilterComboBox;

	UPROPERTY(EditDefaultsOnly, Category = "AnyPrint", meta = (DisplayName = "AnyPrintLog Class"))
	TSubclassOf<UAnyPrintLog> AnyPrintLogClass;

	UFUNCTION()
	void OnLogCreated(FLogInfo LogInfo);

	/* LogScrollBox */
	void UpdateLogScrollBox();

	UFUNCTION()
	void ClearLogScrollBox();
	
	/* Font Info */
	void GetFontInfo();
	void SetLogTextFontInfo(float LogTextSize);
	void SetDetailsTextFontInfo(float DetailsTextSize);
	void SetLogTextInfo(UAnyPrintLog* LogWidget, FLogInfo LogInfo);

	static TWeakObjectPtr<UAnyPrintManager> ActiveManager;
	static UAnyPrintManager* GetActiveManager();

	void ResizeLogScrollBox();
};
