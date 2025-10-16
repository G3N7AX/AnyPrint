// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnyPrintConfig/Public/AnyPrintSettings.h"
#include "Components/CheckBox.h"
#include "AnyPrintMenu.generated.h"

class UScrollBox;
class UTextBlock;
class UCheckBox;
class UEditableTextBox;

/**
 * 
 */

UCLASS()
class ANYPRINTEDITOR_API UAnyPrintMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	void GetDefaultOptions();
	void BindOptions();

	UPROPERTY(meta = (BindWidget))
	UScrollBox* MenuScrollBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* UnifyTextSizeText;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* UnifyTextSizeCheckBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WrapLogText;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* WrapLogCheckBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LogTextSizeText;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* LogTextSizeTextBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DetailsTextSizeText;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* DetailsTextSizeTextBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Use12hrFormatText;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* Use12hrFormatCheckBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScrollToBottomText;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* ScrollToBottomCheckBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxLogCountText;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* MaxLogCountTextBox;

	UFUNCTION()
	void OnUnifyTextSizeChanged(bool IsChecked);

	UFUNCTION()
	void OnWrapLogTextChanged(bool IsChecked);

	UFUNCTION()
	void OnTimeFormatChanged(bool IsChecked);

	UFUNCTION()
	void OnScrollToBottomChanged(bool IsChecked);

	UFUNCTION()
	void OnLogTextChanged(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnDetailsTextChanged(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnMaxLogCountChanged(const FText& Text, ETextCommit::Type CommitMethod);

	void UnifyLogTextSize();
	void UnifyDetailsTextSize();
};
