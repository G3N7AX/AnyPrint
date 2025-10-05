// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyPrintWidget.h"
#include "AnyPrintSettings.h"
#include "AnyPrintLibrary/Public/AnyPrintFunctionLibrary.h"
#include "Components/TextBlock.h"
#include "Styling/CoreStyle.h"

void UAnyPrintWidget::PopulateWidget(FLogInfo LogInfo)
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();

	PrimaryFontInfo = LogTextBlock->GetFont();
	SecondaryFontInfo = TimeStampTextBlock->GetFont();
	
	PrimaryFontInfo.Size = Settings->LogTextSize;
	SecondaryFontInfo.Size = Settings->DetailTextSize;

	LogColor = LogInfo.Color;
	
	LogTextBlock->SetText(LogInfo.Log);
	TimeStampTextBlock->SetText(FText::FromString(TEXT("TimeStamp: ") + LogInfo.TimeStamp.ToString()));
	CategoryTextBlock->SetText(FText::FromString(TEXT("Category: ") + LogInfo.Category.ToString()));

	LogTextBlock->SetFont(PrimaryFontInfo);
	TimeStampTextBlock->SetFont(SecondaryFontInfo);
	CategoryTextBlock->SetFont(SecondaryFontInfo);

	LogTextBlock->SetColorAndOpacity(LogColor);
}
