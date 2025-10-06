// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyPrintSettings.h"

UAnyPrintSettings::UAnyPrintSettings()
{
	if (bUnifyTextSizes == true)
	{
		DetailTextSize = FMath::RoundToFloat(DetailTextSize * 2.0f) / 2.0f;
	}
	
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

	if (ChangedSetting == GET_MEMBER_NAME_CHECKED(UAnyPrintSettings, LogTextSize) && bUnifyTextSizes == true)
	{
		UnifyDetailTextSize();
	}
}

void UAnyPrintSettings::UnifyLogTextSize()
{
	LogTextSize = DetailTextSize * 1.5f;
	LogTextSize = FMath::RoundToFloat(LogTextSize * 2.0f) / 2.0f;

	if (LogTextSize < 12.f)
	{
		LogTextSize = 12.f;
	}
}


void UAnyPrintSettings::UnifyDetailTextSize()
{
	DetailTextSize = LogTextSize / 1.5f;
	DetailTextSize = FMath::RoundToFloat(DetailTextSize * 2.0f) / 2.0f;;

	if (DetailTextSize < 8.f)
	{
		DetailTextSize = 8.f;
	}
}

