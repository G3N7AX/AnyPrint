// Fill out your copyright notice in the Description page of Project Settings.


#include "AnyPrintConsole.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UAnyPrintConsole::NativeConstruct()
{
	ConsoleButton->OnClicked.AddDynamic(this, &UAnyPrintConsole::ShowIndexZero);
	SettingsButton->OnClicked.AddDynamic(this, &UAnyPrintConsole::ShowIndexOne);
}

void UAnyPrintConsole::ShowIndexZero()
{
	PanelSwitcher->SetActiveWidgetIndex(0);
}

void UAnyPrintConsole::ShowIndexOne()
{
	PanelSwitcher->SetActiveWidgetIndex(1);
}