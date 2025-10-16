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

	UPROPERTY(
		Config,
		VisibleDefaultsOnly,
		Category = "Format",
		meta = (
			DisplayName = "Unify Text Size",
			ToolTip = ""))
	bool bUnifyTextSize = true;
	
	UPROPERTY(
	Config,
	VisibleDefaultsOnly,
	Category = "Format",
	meta = (
		DisplayName = "Wrap Log Text",
		ToolTip = ""))
	bool bWrapLogText = true;

	UPROPERTY(
	Config,
	VisibleDefaultsOnly,
	Category = "Format",
	meta = (
		DisplayName = "Use 12hr Format",
		ToolTip = ""))
	bool bUse12hrFormat = false;

	UPROPERTY(
	Config,
	VisibleDefaultsOnly,
	Category = "Display",
	meta = (
		DisplayName = "Log Text Size",
		ToolTip = ""))
	float LogTextSize = 12;

	UPROPERTY(
	Config,
	VisibleDefaultsOnly,
	Category = "Display",
	meta = (
		DisplayName = "Details Text Size",
		ToolTip = ""))
	float DetailsTextSize = 8;

	UPROPERTY(
	Config,
	VisibleDefaultsOnly,
	Category = "Behavior",
	meta = (
		DisplayName = "Scroll To Bottom",
		ToolTip = ""))
	bool bScrollToBottom = true;
	
	UPROPERTY(
		Config,
		VisibleDefaultsOnly,
		Category = "Behavior",
		meta = (
			DisplayName = "Max Log Count",
			ToolTip = ""))
	int32 MaxLogCount = 1000;
	
	UPROPERTY(
		Config,
		EditAnywhere,
		Category = "Categories",
		meta = (
			DisplayName = "Categories",
			ToolTip = ""))
	TMap<FName, FColor> Categories;
};
