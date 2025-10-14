// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyPrintLogManager.h"
#include "AnyPrintSettings.h"
#include "AnyPrintLibrary/Public/AnyPrintFunctionLibrary.h"
#include "AnyPrintLog.h"
#include "Components/Button.h"
#include "Components/ComboBoxKey.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

TWeakObjectPtr<UAnyPrintLogManager> UAnyPrintLogManager::ActiveManager = nullptr;

void UAnyPrintLogManager::NativeConstruct()
{
	Super::NativeConstruct();
	
	ClearButton->OnClicked.AddDynamic(this, &UAnyPrintLogManager::ClearLogScrollBox);
	
	UAnyPrintFunctionLibrary::OnLogCreated.BindUObject(this, &UAnyPrintLogManager::OnLogCreated);

	GetFontInfo();

	ActiveManager = this;
}

void UAnyPrintLogManager::OnLogCreated(FLogInfo LogInfo)
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

void UAnyPrintLogManager::UpdateLogScrollBox()
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

void UAnyPrintLogManager::ClearLogScrollBox()
{
	LogEntries.Empty();
	LogScrollBox->ClearChildren();
}

void UAnyPrintLogManager::GetFontInfo()
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();

	LogFontInfo = FCoreStyle::GetDefaultFontStyle("Regular", Settings->LogTextSize);
	DetailsFontInfo = FCoreStyle::GetDefaultFontStyle("Regular", Settings->DetailsTextSize);
}

void UAnyPrintLogManager::SetLogTextFontInfo(float LogTextSize)
{
	LogFontInfo.Size = LogTextSize;
}

void UAnyPrintLogManager::SetDetailsTextFontInfo(float DetailsTextSize)
{
	DetailsFontInfo.Size = DetailsTextSize;
}

void UAnyPrintLogManager::SetLogTextInfo(UAnyPrintLog* LogWidget, FLogInfo LogInfo)
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();
	
	LogWidget->LogText->SetText(LogInfo.Log);
	LogWidget->LogText->SetFont(LogFontInfo);
	LogWidget->LogText->SetColorAndOpacity(LogInfo.Color);
	LogWidget->LogText->SetAutoWrapText(Settings->bWrapLogText);
}

UAnyPrintLogManager* UAnyPrintLogManager::GetActiveManager()
{
		return ActiveManager.Get();
}

void UAnyPrintLogManager::ResizeLogScrollBox()
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

