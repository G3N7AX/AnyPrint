// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnyPrintLog.generated.h"

class UExpandableArea;
class UTextBlock;

/**
 * 
 */

UCLASS()
class ANYPRINTEDITOR_API UAnyPrintLog : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget))
	UExpandableArea* ExpandableLogArea;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LogText;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* TimeStampText;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* CategoryText;

	UFUNCTION()
	void SetDetailsText(FLogInfo LogInfo);
};
