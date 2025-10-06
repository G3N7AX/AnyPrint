// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyPrintConsole.h"
#include "AnyPrintConfig/Public/AnyPrintSettings.h"
#include "AnyPrintLibrary/Public/AnyPrintFunctionLibrary.h"
#include "Components/Button.h"
#include "Components/ComboBoxKey.h"
#include "Components/ScrollBox.h"


void UAnyPrintConsole::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	UAnyPrintFunctionLibrary::OnLogCreated.BindUObject(this, &UAnyPrintConsole::OnLogReceived);
	
	ClearLogsButton->OnClicked.AddUniqueDynamic(this, &UAnyPrintConsole::OnClearLogs);
	
	if (!UAnyPrintFunctionLibrary::OnLogCreated.IsBound() && ClearLogsButton->OnClicked.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("DELEGATES ARE NOT BOUND!"));
		UE_LOG(LogTemp, Warning, TEXT("If you've just opened the Console for the first time, try restarting the editor. If you don't see this warning after that then you're good to go."));
	}
}

void UAnyPrintConsole::OnLogReceived(FLogInfo LogInfo)
{
	LogEntries.Add(LogInfo);
	
	CreateLogWidget(LogInfo);
}

void UAnyPrintConsole::CreateLogWidget(FLogInfo LogInfo)
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();
	
	if (LogScrollBox->GetChildrenCount() <= Settings->MaxLogCount)
	{
		UAnyPrintWidget* LogWidget = CreateWidget<UAnyPrintWidget>(this, LogWidgetClass);
		LogScrollBox->AddChild(LogWidget);

		LogWidget->PopulateWidget(LogInfo);
	}
	
	else
	{
		LogScrollBox->RemoveChildAt(0);

		UAnyPrintWidget* LogWidget = CreateWidget<UAnyPrintWidget>(this, LogWidgetClass);
		LogScrollBox->AddChild(LogWidget);

		LogWidget->PopulateWidget(LogInfo);
	}
	
	LogScrollBox->ScrollToEnd();
}

void UAnyPrintConsole::OnClearLogs()
{
	LogScrollBox->ClearChildren();
	LogEntries.Empty();
}

