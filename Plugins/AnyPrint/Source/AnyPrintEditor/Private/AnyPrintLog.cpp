// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyPrintLog.h"
#include "AnyPrintLibrary/Public/AnyPrintFunctionLibrary.h"
#include "Components/TextBlock.h"

void UAnyPrintLog::SetDetailsText(FLogInfo LogInfo)
{
	if (TimeStampText && CategoryText)
	{
		TimeStampText->SetText(FText::FromString(LogInfo.TimeStamp.ToString()));
		CategoryText->SetText(FText::FromString(LogInfo.Category.ToString()));
	}
}
