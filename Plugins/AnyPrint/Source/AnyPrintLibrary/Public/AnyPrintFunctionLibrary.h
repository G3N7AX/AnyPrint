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
	TimeStamp(FText::GetEmpty()),
	Log(FText::GetEmpty()),
	Category(FText::GetEmpty()),
	Color(FColor::White) {};
};

DECLARE_DELEGATE_OneParam(FOnLogCreated, FLogInfo);

UCLASS()
class ANYPRINTLIBRARY_API UAnyPrintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:

	static FText CreateTimeStamp();
	static FColor GetLogColor(FName Category);
	static void PopulateLogStruct(FText Log, FName Category);

	static FLogInfo LogInfo;
	static FOnLogCreated OnLogCreated;
	
	UFUNCTION(BlueprintCallable, Category="AnyPrint", DisplayName="PrintAnything (String)")
	static void PrintAnything(UPARAM(meta = (GetOptions = "GetCategoryKeys")) FName Category, FString Log);
	static void PrintAnything(UPARAM(meta = (GetOptions = "GetCategoryKeys")) FName Category, FVector VectorLog);
	static void PrintAnything(UPARAM(meta = (GetOptions = "GetCategoryKeys")) FName Category, FRotator RotationLog);
	
	UFUNCTION()
	TArray<FName> GetCategoryKeys() const;
	
};
