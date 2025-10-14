// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyPrintManager.h"
#include "AnyPrintSettings.h"
#include "AnyPrintLibrary/Public/AnyPrintFunctionLibrary.h"
#include "AnyPrintLog.h"
#include "Components/Button.h"
#include "Components/ComboBoxKey.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

TWeakObjectPtr<UAnyPrintManager> UAnyPrintManager::ActiveManager = nullptr;

void UAnyPrintManager::NativeConstruct()
{
	Super::NativeConstruct();
	
	ClearButton->OnClicked.AddDynamic(this, &UAnyPrintManager::ClearLogScrollBox);
	
	UAnyPrintFunctionLibrary::OnLogCreated.BindUObject(this, &UAnyPrintManager::OnLogCreated);

	GetFontInfo();

	ActiveManager = this;
}

void UAnyPrintManager::OnLogCreated(FLogInfo LogInfo)
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();
	
	UAnyPrintLog* AnyPrintLog = CreateWidget<UAnyPrintLog>(this, AnyPrintLogClass);
	
	SetLogTextInfo(AnyPrintLog, LogInfo);
	
	AnyPrintLog->SetDetailsText(LogInfo);

	if (LogScrollBox->GetChildrenCount() >= Settings->MaxLogCount)
	{
		LogEntries.RemoveAt(0);
		LogScrollBox->RemoveChildAt(0);
		
		LogEntries.Add(AnyPrintLog);
		LogScrollBox->AddChild(AnyPrintLog);
	}
	else
	{
		LogEntries.Add(AnyPrintLog);
		LogScrollBox->AddChild(AnyPrintLog);
	}
	
	if (Settings->bScrollToBottom)
	{
		LogScrollBox->ScrollToEnd();
	}
}

void UAnyPrintManager::UpdateLogScrollBox()
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();
	
	if (!LogEntries.IsEmpty())
	{
		LogScrollBox->ClearChildren();
		
		for (UAnyPrintLog* LogEntry : LogEntries)
		{
			if (!LogEntry->LogText)
			{
				LogEntries.Empty();
				continue;
			};

			LogEntry->LogText->SetFont(LogFontInfo);
			LogEntry->LogText->SetAutoWrapText(Settings->bWrapLogText);
			LogEntry->LogText->InvalidateLayoutAndVolatility();

			LogEntry->TimeStampText->SetFont(DetailsFontInfo);
			LogEntry->TimeStampText->InvalidateLayoutAndVolatility();
			
			LogEntry->CategoryText->SetFont(DetailsFontInfo);
			LogEntry->CategoryText->InvalidateLayoutAndVolatility();
			
			LogScrollBox->AddChild(LogEntry);
		}

		if (Settings->bScrollToBottom)
		{
			LogScrollBox->ScrollToEnd();
		}
	}
}

void UAnyPrintManager::ClearLogScrollBox()
{
	LogEntries.Empty();
	LogScrollBox->ClearChildren();
}

void UAnyPrintManager::GetFontInfo()
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();

	LogFontInfo = FCoreStyle::GetDefaultFontStyle("Regular", Settings->LogTextSize);
	DetailsFontInfo = FCoreStyle::GetDefaultFontStyle("Regular", Settings->DetailsTextSize);
}

void UAnyPrintManager::SetLogTextFontInfo(float LogTextSize)
{
	LogFontInfo.Size = LogTextSize;
}

void UAnyPrintManager::SetDetailsTextFontInfo(float DetailsTextSize)
{
	DetailsFontInfo.Size = DetailsTextSize;
}

void UAnyPrintManager::SetLogTextInfo(UAnyPrintLog* LogWidget, FLogInfo LogInfo)
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();
	
	LogWidget->LogText->SetText(LogInfo.Log);
	LogWidget->LogText->SetFont(LogFontInfo);
	LogWidget->LogText->SetColorAndOpacity(LogInfo.Color);
	LogWidget->LogText->SetAutoWrapText(Settings->bWrapLogText);
}

UAnyPrintManager* UAnyPrintManager::GetActiveManager()
{
		return ActiveManager.Get();
}

void UAnyPrintManager::ResizeLogScrollBox()
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();

	if (LogScrollBox->GetChildrenCount() > Settings->MaxLogCount)
	{
		int32 LogCount = LogScrollBox->GetChildrenCount();

		int32 AmountToRemove = LogScrollBox->GetChildrenCount() - Settings->MaxLogCount;

		UAnyPrintFunctionLibrary::PrintAnything(FName("Low"), FString::Printf(TEXT("%i"), AmountToRemove));

		LogEntries.RemoveAt(0, AmountToRemove);

		UpdateLogScrollBox();
	}
}

