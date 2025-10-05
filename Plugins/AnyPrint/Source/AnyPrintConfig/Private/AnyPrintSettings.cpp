// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyPrintSettings.h"

UAnyPrintSettings::UAnyPrintSettings()
{
	if (Categories.IsEmpty())
	{
		Categories.Add(TEXT("Low"), FColor::White);
		Categories.Add(TEXT("Medium"), FColor::Yellow);
		Categories.Add(TEXT("High"), FColor::Orange);
		Categories.Add(TEXT("Severe"), FColor::Red);
	}
}

void UAnyPrintSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedSetting = PropertyChangedEvent.Property ? PropertyChangedEvent.GetPropertyName() : NAME_None;

	if (ChangedSetting == GET_MEMBER_NAME_CHECKED(UAnyPrintSettings, LogTextSize))
	{
		DetailTextSize = LogTextSize / 2;

		if (DetailTextSize < 8.f)
		{
			DetailTextSize = 8.f;

			UE_LOG(LogTemp, Log, TEXT("LogTextSize: %f"), DetailTextSize);
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Settings Changed"));
}
