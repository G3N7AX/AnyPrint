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

	UPROPERTY(Config, EditAnywhere, meta = (DisplayName = "Log Text Size"))
	float LogTextSize = 16.f;
	
	UPROPERTY(Config, EditAnywhere, meta = (DisplayName = "Detail Text Size"))
	float DetailTextSize;

	UPROPERTY(Config, EditAnywhere, meta =
		(DisplayName = "Use 12hr TimeStamp" ,ToolTip = "This option determines if a 12hr or 24hr time format will be used for TimeStamps"))
	bool bUse12hrTimeStamp = false;

	UPROPERTY(Config, EditAnywhere, meta =
		(DisplayName = "Unify Text Sizes" ,ToolTip = "This option determines if the Detail Text Size will be manually or automatically set. ON will automatically make the default Detail Text Size half of what the Log Text Size is (min: 8)."))
	bool bUnifyTextSizes = true;

	UPROPERTY(Config, EditAnywhere)
	TMap<FName, FColor> Categories;

	void UnifyLogTextSize();
	void UnifyDetailTextSize();
};
