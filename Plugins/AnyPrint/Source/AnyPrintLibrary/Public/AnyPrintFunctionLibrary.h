// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AnyPrintFunctionLibrary.generated.h"

/**
 * 
 */

USTRUCT()
struct FLogInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FText TimeStamp;

	UPROPERTY()
	FText Log;

	UPROPERTY()
	FText Category;

	UPROPERTY()
	FColor Color;

	FLogInfo() :
	TimeStamp(FText::FromString("")),
	Log(FText::FromString("")),
	Category(FText::FromString("")),
	Color(FColor::White) {}
};

DECLARE_DELEGATE_OneParam(FOnLogCreated, FLogInfo);

UCLASS()
class ANYPRINTLIBRARY_API UAnyPrintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/* Declare Struct */
	static FLogInfo LogInfo;

	/* Declare Delegate */
	static FOnLogCreated OnLogCreated;

	UFUNCTION(BlueprintCallable, meta = (DevelopmentOnly))
	static void PrintAnything(
		UPARAM(meta = (GetOptions = "GetCategoryKeys"))
		FName SelectedCategory,
		FString Log
		);

	// static TArray<FName> GetCategoryKeys();
	
	UFUNCTION()
	TArray<FName> GetCategoryKeys() const;

	static FText CreateTimeStamp();
	static FColor GetCategoryColor(FName Category);

	static void BuildLogStruct(FText TimeStamp, FText Log, FText Category, FColor Color);
	
private:

	
};
