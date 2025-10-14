// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyPrintMenu.h"
#include "AnyPrintConfig/Public/AnyPrintSettings.h"
#include "AnyPrintFunctionLibrary.h"
#include "AnyPrintManager.h"
#include "Components/EditableTextBox.h"


void UAnyPrintMenu::NativeConstruct()
{
	UAnyPrintSettings* Settings = GetMutableDefault<UAnyPrintSettings>();

	Settings->LoadConfig();

	BindOptions();
	GetDefaultOptions();
}

void UAnyPrintMenu::BindOptions()
{
	UnifyTextSizeCheckBox->OnCheckStateChanged.AddDynamic(this, &UAnyPrintMenu::OnUnifyTextSizeChanged);
	WrapLogCheckBox->OnCheckStateChanged.AddDynamic(this, &UAnyPrintMenu::OnWrapLogTextChanged);
	Use12hrFormatCheckBox->OnCheckStateChanged.AddDynamic(this, &UAnyPrintMenu::OnTimeFormatChanged);
	ScrollToBottomCheckBox->OnCheckStateChanged.AddDynamic(this, &UAnyPrintMenu::OnScrollToBottomChanged);
	
	LogTextSizeTextBox->OnTextCommitted.AddDynamic(this, &UAnyPrintMenu::OnLogTextChanged);
	DetailsTextSizeTextBox->OnTextCommitted.AddDynamic(this, &UAnyPrintMenu::OnDetailsTextChanged);
	ConsoleTextSizeTextBox->OnTextCommitted.AddDynamic(this, &UAnyPrintMenu::OnConsoleTextChanged);
	MaxLogCountTextBox->OnTextCommitted.AddDynamic(this, &UAnyPrintMenu::OnMaxLogCountChanged);
}


void UAnyPrintMenu::GetDefaultOptions()
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();
	
	UnifyTextSizeCheckBox->SetIsChecked(Settings->bUnifyTextSize);
	WrapLogCheckBox->SetIsChecked(Settings->bWrapLogText);
	Use12hrFormatCheckBox->SetIsChecked(Settings->bUse12hrFormat);
	ScrollToBottomCheckBox->SetIsChecked(Settings->bScrollToBottom);

	LogTextSizeTextBox->SetMinDesiredWidth(50.f);
	LogTextSizeTextBox->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), Settings->LogTextSize)));
	LogTextSizeTextBox->SetJustification(ETextJustify::Center);
	
	DetailsTextSizeTextBox->SetMinDesiredWidth(50.f);
	DetailsTextSizeTextBox->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), Settings->DetailsTextSize)));
	DetailsTextSizeTextBox->SetJustification(ETextJustify::Center);

	ConsoleTextSizeTextBox->SetMinDesiredWidth(50.f);
	ConsoleTextSizeTextBox->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), Settings->ConsoleTextSize)));
	ConsoleTextSizeTextBox->SetJustification(ETextJustify::Center);

	MaxLogCountTextBox->SetMinDesiredWidth(50.f);
	MaxLogCountTextBox->SetText(FText::FromString(FString::Printf(TEXT("%i"), Settings->MaxLogCount)));
	MaxLogCountTextBox->SetJustification(ETextJustify::Center);
}

void UAnyPrintMenu::OnUnifyTextSizeChanged(bool IsChecked)
{
	UAnyPrintSettings* Settings = GetMutableDefault<UAnyPrintSettings>();

	Settings->bUnifyTextSize = IsChecked;
	Settings->TryUpdateDefaultConfigFile();
}

void UAnyPrintMenu::OnWrapLogTextChanged(bool IsChecked)
{
	UAnyPrintSettings* Settings = GetMutableDefault<UAnyPrintSettings>();

	Settings->bWrapLogText = IsChecked;
	Settings->TryUpdateDefaultConfigFile();

	UAnyPrintManager* LogManager = UAnyPrintManager::GetActiveManager();

	LogManager->UpdateLogScrollBox();
}

void UAnyPrintMenu::OnTimeFormatChanged(bool IsChecked)
{
	UAnyPrintSettings* Settings = GetMutableDefault<UAnyPrintSettings>();

	Settings->bUse12hrFormat = IsChecked;
	Settings->TryUpdateDefaultConfigFile();
}

void UAnyPrintMenu::OnScrollToBottomChanged(bool IsChecked)
{
	UAnyPrintSettings* Settings = GetMutableDefault<UAnyPrintSettings>();

	Settings->bScrollToBottom = IsChecked;
	Settings->TryUpdateDefaultConfigFile();
}

void UAnyPrintMenu::OnLogTextChanged(const FText& Text, ETextCommit::Type CommitMethod)
{
	UAnyPrintSettings* Settings = GetMutableDefault<UAnyPrintSettings>();

	FString LogTextSizeStr = Text.ToString();
	float LogTextSize = FCString::Atof(*LogTextSizeStr);

	if (LogTextSize < 12.f)
	{
		LogTextSize = 12.f;
	}
	
	Settings->LogTextSize = LogTextSize;

	if (Settings->bUnifyTextSize)
	{
		UnifyDetailsTextSize();
	}
	
	UAnyPrintManager* LogManager = UAnyPrintManager::GetActiveManager();
	
	LogManager->SetLogTextFontInfo(LogTextSize);
	LogManager->UpdateLogScrollBox();
}

void UAnyPrintMenu::OnDetailsTextChanged(const FText& Text, ETextCommit::Type CommitMethod)
{
	UAnyPrintSettings* Settings = GetMutableDefault<UAnyPrintSettings>();

	FString DetailsTextSizeStr = Text.ToString();
	float DetailsTextSize = FCString::Atof(*DetailsTextSizeStr);

	if (DetailsTextSize < 8.f)
	{
		DetailsTextSize = 8.f;
	}
	
	Settings->DetailsTextSize = DetailsTextSize;

	if (Settings->bUnifyTextSize)
	{
		UnifyLogTextSize();
	}

	UAnyPrintManager* LogManager = UAnyPrintManager::GetActiveManager();

	LogManager->SetDetailsTextFontInfo(DetailsTextSize);
	LogManager->UpdateLogScrollBox();
}

void UAnyPrintMenu::OnConsoleTextChanged(const FText& Text, ETextCommit::Type CommitMethod)
{
	UAnyPrintSettings* Settings = GetMutableDefault<UAnyPrintSettings>();

	FString ConsoleTextSize = Text.ToString();
	
	Settings->ConsoleTextSize = FCString::Atof(*ConsoleTextSize);

	UAnyPrintFunctionLibrary::PrintAnything(FName("Medium"), ConsoleTextSize);
}

void UAnyPrintMenu::OnMaxLogCountChanged(const FText& Text, ETextCommit::Type CommitMethod)
{
	UAnyPrintSettings* Settings = GetMutableDefault<UAnyPrintSettings>();

	FString MaxLogCount = Text.ToString();
	
	Settings->MaxLogCount = FCString::Atoi(*MaxLogCount);

	// UAnyPrintFunctionLibrary::PrintAnything(FName("Medium"), MaxLogCount);

	UAnyPrintManager* LogManager = UAnyPrintManager::GetActiveManager();

	LogManager->ResizeLogScrollBox();
}

void UAnyPrintMenu::UnifyLogTextSize()
{
	UAnyPrintSettings* Settings = GetMutableDefault<UAnyPrintSettings>();

	Settings->LogTextSize = FMath::RoundToFloat((Settings->DetailsTextSize * 1.5f) * 2.0f) / 2.0f;

	if (Settings->LogTextSize < 12.f)
	{
		Settings->LogTextSize = 12.f;	
	}

	LogTextSizeTextBox->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), Settings->LogTextSize)));

	UAnyPrintManager* LogManager = UAnyPrintManager::GetActiveManager();

	LogManager->SetLogTextFontInfo(Settings->LogTextSize);
}

void UAnyPrintMenu::UnifyDetailsTextSize()
{
	UAnyPrintSettings* Settings = GetMutableDefault<UAnyPrintSettings>();

	Settings->DetailsTextSize = FMath::RoundToFloat((Settings->LogTextSize / 1.5f) * 2.0f) / 2.0f;

	if (Settings->DetailsTextSize < 8.f)
	{
		Settings->DetailsTextSize = 8.f;	
	}
	
	DetailsTextSizeTextBox->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), Settings->DetailsTextSize)));

	UAnyPrintManager* LogManager = UAnyPrintManager::GetActiveManager();

	LogManager->SetDetailsTextFontInfo(Settings->DetailsTextSize);
}
