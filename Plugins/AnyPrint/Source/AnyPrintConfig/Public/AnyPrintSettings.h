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

	UPROPERTY(Config, EditAnywhere, meta = (
		Category = "Appearance",
		DisplayName = "Log Text Size",
		ToolTip = "Default: 12"))
	float LogTextSize = 12.f;
	
	UPROPERTY(Config, EditAnywhere, meta = (
		Category = "Appearance",
		DisplayName = "Detail Text Size"))
	float DetailTextSize;

	UPROPERTY(Config, EditAnywhere, meta =(
		Category = "Appearance",
		DisplayName = "Wrap Log Text",
		ToolTip = "When enabled, the Log Text Block will wrap the text if it exceeds the boundaries of the Console."))
	bool bWrapLogText = false;
	
	UPROPERTY(Config, EditAnywhere, meta =(
		Category = "Appearance",
		DisplayName = "Use 12hr TimeStamp",
		ToolTip = "When enabled, TimeStamps are created in 12hr format."))
	bool bUse12hrTimeStamp = false;

	UPROPERTY(Config, EditAnywhere, meta =(
		Category = "Appearance",
		DisplayName = "Unify Text Sizes",
		ToolTip = "When enabled, both Log Text Size and Detail Text Size will scale together, with Detail Text Size always set to roughly two-thirds of Log Text Size. When disabled, text sizes can be set manually and are no longer linked."))
	bool bUnifyTextSizes = true;

	UPROPERTY(Config, EditAnywhere, meta = (
		Category = "Appearance",
		DisplayName = "Max Log Count",
		Tooltip = "The maximum amount of logs that the Console can hold (Default: 1000)"))
	int32 MaxLogCount = 1000;

	UPROPERTY(Config, EditAnywhere)
	TMap<FName, FColor> Categories;

	void UnifyLogTextSize();
	void UnifyDetailTextSize();
};
