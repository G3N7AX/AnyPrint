// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnyPrintWidget.generated.h"

class UExpandableArea;
class UTextBlock;

struct FSlateFontInfo;
struct FSlateColor;

/**
 * 
 */

UCLASS()
class ANYPRINTEDITOR_API UAnyPrintWidget : public UUserWidget
{
	GENERATED_BODY()


	
public:

	FSlateFontInfo PrimaryFontInfo;
	FSlateFontInfo SecondaryFontInfo;

	FSlateColor LogColor;

	UPROPERTY(meta = (BindWidget))
	UExpandableArea* LogStage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LogTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeStampTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CategoryTextBlock;

	UFUNCTION()
	void PopulateWidget(FLogInfo LogInfo);
};
