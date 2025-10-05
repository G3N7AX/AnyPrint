// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyPrintConsole.h"
#include "AnyPrintConfig/Public/AnyPrintSettings.h"
#include "AnyPrintLibrary/Public/AnyPrintFunctionLibrary.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"


void UAnyPrintConsole::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	UAnyPrintFunctionLibrary::OnLogCreated.BindUObject(this, &UAnyPrintConsole::OnLogReceived);
	
	ClearLogsButton->OnClicked.AddUniqueDynamic(this, &UAnyPrintConsole::OnClearLogs);
	
	if (UAnyPrintFunctionLibrary::OnLogCreated.IsBound() && ClearLogsButton->OnClicked.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("Delegates Bound"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Delegates Not Bound"));
	}
}

void UAnyPrintConsole::OnLogReceived(FLogInfo LogInfo)
{
	LogEntries.Add(LogInfo);

	UE_LOG(LogTemp, Warning, TEXT("Log Received by Listener"));
	UE_LOG(LogTemp, Warning, TEXT("%s | %s | %s | %s"), *LogInfo.TimeStamp.ToString(), *LogInfo.Log.ToString(), *LogInfo.Category.ToString(), *LogInfo.Color.ToString());
	
	CreateLogWidget(LogInfo);
}

void UAnyPrintConsole::CreateLogWidget(FLogInfo LogInfo)
{
	UAnyPrintWidget* LogWidget = CreateWidget<UAnyPrintWidget>(this, LogWidgetClass);
	LogScrollBox->AddChild(LogWidget);

	LogWidget->PopulateWidget(LogInfo);
	
	LogScrollBox->ScrollToEnd();
}

void UAnyPrintConsole::OnClearLogs()
{
	LogScrollBox->ClearChildren();

	LogEntries.Empty();
}
