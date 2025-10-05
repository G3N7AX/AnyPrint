// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AnyPrintSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "AnyPrint"))
class ANYPRINTCONFIG_API UAnyPrintSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UAnyPrintSettings();

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	UPROPERTY(Config, EditAnywhere)
	float LogTextSize = 12.f;
	
	UPROPERTY(Config, EditAnywhere)
	float DetailTextSize = LogTextSize / 2;

	UPROPERTY(Config, EditAnywhere)
	TMap<FName, FColor> Categories;
};
