// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyPrintFunctionLibrary.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "AnyPrintConfig/Public/AnyPrintSettings.h"
#include "Misc/DateTime.h"

FLogInfo UAnyPrintFunctionLibrary::LogInfo;
FOnLogCreated UAnyPrintFunctionLibrary::OnLogCreated;

void UAnyPrintFunctionLibrary::PrintAnything(FName Category, FString Log)
{
	FText LogText = FText::FromString(Log);
	PopulateLogStruct(LogText, Category);
}

void UAnyPrintFunctionLibrary::PrintAnything(FName Category, FVector VectorLog)
{
	FText LogText = FText::FromString(FString::Printf(TEXT("X: %02f Y: %02f Z: %02f"), VectorLog.X, VectorLog.Y, VectorLog.Z));
	PopulateLogStruct(LogText, Category);
}

void UAnyPrintFunctionLibrary::PrintAnything(FName Category, FRotator RotationLog)
{
	FText LogText = FText::FromString(FString::Printf(TEXT("P: %02f Y: %02f R: %02f"), RotationLog.Pitch, RotationLog.Yaw, RotationLog.Roll));
	PopulateLogStruct(LogText, Category);
}

TArray<FName> UAnyPrintFunctionLibrary::GetCategoryKeys() const
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();

	TArray<FName> CategoryKeys;
	
	for (auto& Category : Settings->Categories)
	{
		CategoryKeys.AddUnique(Category.Key);
	}

	return CategoryKeys;
}

FText UAnyPrintFunctionLibrary::CreateTimeStamp()
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();
	
	FDateTime CurrentTIme = FDateTime::Now();

	int32 Hour = Settings->bUse12hrFormat ? CurrentTIme.GetHour12() : CurrentTIme.GetHour();
	int32 Minute = CurrentTIme.GetMinute();
	int32 Second = CurrentTIme.GetSecond();

	FText TimeStamp = FText::FromString(FString::Printf(TEXT("%02d:%02d:%02d"), Hour, Minute, Second));
	
	return TimeStamp;
}

FColor UAnyPrintFunctionLibrary::GetLogColor(FName Category)
{
	const UAnyPrintSettings* Settings = GetDefault<UAnyPrintSettings>();

	FColor LogColor = FColor::Transparent;
	
	for (auto& Color : Settings->Categories)
	{
		LogColor = Settings->Categories.FindRef(Category);
	}

	return LogColor;
}

void UAnyPrintFunctionLibrary::PopulateLogStruct(FText Log, FName Category)
{
	LogInfo.TimeStamp = CreateTimeStamp();
	LogInfo.Log = Log;
	LogInfo.Category = FText::FromString(Category.ToString());
	LogInfo.Color = GetLogColor(Category);

	OnLogCreated.ExecuteIfBound(LogInfo);
}
