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
