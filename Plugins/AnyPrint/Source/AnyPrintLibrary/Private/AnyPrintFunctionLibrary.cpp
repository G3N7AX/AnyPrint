// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyPrintFunctionLibrary.h"
#include "AnyPrintSettings.h"
#include "Misc/DateTime.h"

/* Initialize Struct */
FLogInfo UAnyPrintFunctionLibrary::LogInfo = FLogInfo();

/* Initialize Struct */
FOnLogCreated UAnyPrintFunctionLibrary::OnLogCreated = FOnLogCreated();

void UAnyPrintFunctionLibrary::PrintAnything(FName SelectedCategory, FString Log)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Log);

	FColor Color = GetCategoryColor(SelectedCategory);
	FText TimeStamp = CreateTimeStamp();
	FText LogText = FText::FromString(Log);
	FText Category = FText::FromString(SelectedCategory.ToString());
	
	BuildLogStruct(TimeStamp, LogText, Category, Color);
}

TArray<FName> UAnyPrintFunctionLibrary::GetCategoryKeys() const
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();

	TArray<FName> Keys;
	
	for (auto& Category : Settings->Categories)
	{
		Keys.Add(Category.Key);
	}

	return Keys;
}

FText UAnyPrintFunctionLibrary::CreateTimeStamp()
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();

	FText TimeStamp;

	int Hour, Minute, Second;
	
	const FDateTime Now = FDateTime::Now();

	if (Settings->bUse12hrTimeStamp == false)
	{
		Hour = Now.GetHour();
		Minute = Now.GetMinute();
		Second = Now.GetSecond();

		const FString TimeStampString = FString::Printf(TEXT("%02d:%02d:%02d"), Hour, Minute, Second);
	
		TimeStamp = FText::FromString(TimeStampString);
	}
	
	else
	{
		Hour = Now.GetHour12();
		Minute = Now.GetMinute();
		Second = Now.GetSecond();

		const FString TimeStampString = FString::Printf(TEXT("%02d:%02d:%02d"), Hour, Minute, Second);
	
		TimeStamp = FText::FromString(TimeStampString);
	}

	return TimeStamp;
}

FColor UAnyPrintFunctionLibrary::GetCategoryColor(FName Category)
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();
	
	const FColor Color = Settings->Categories.FindRef(Category);

	return Color;
}


void UAnyPrintFunctionLibrary::BuildLogStruct(FText TimeStamp, FText Log, FText Category, FColor Color)
{
	LogInfo.TimeStamp = TimeStamp;
	LogInfo.Log = Log;
	LogInfo.Category = Category;
	LogInfo.Color = Color;

	OnLogCreated.ExecuteIfBound(LogInfo);

	UE_LOG(LogTemp, Warning, TEXT("Log Sent"));
}