// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/RootMainMenuWidget.h"
#include "UI/MainMenu/MainMenuWidget.h"
#include "UI/MainMenu/CreditsWidget.h"
#include "UI/Common/SettingsWidget.h"
#include "Components/WidgetSwitcher.h"

void URootMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	WBPMainMenu->OnMenuSettingsClicked.AddDynamic(this, &URootMainMenuWidget::SwitchToSettingsView);
	WBPMainMenu->OnMenuCreditsClicked.AddDynamic(this, &URootMainMenuWidget::SwitchToCreditsView);
	WBPSettings->OnSettingsReturnClicked.AddDynamic(this, &URootMainMenuWidget::SwitchToMainMenuView);
	WBPCredits->OnCreditsReturnClicked.AddDynamic(this, &URootMainMenuWidget::SwitchToMainMenuView);

	SwitchToMainMenuView();
}

void URootMainMenuWidget::SwitchToMainMenuView()
{
	WidgetSwitcherRoot->SetActiveWidgetIndex(EMenuIndex::MainMenu);
}

void URootMainMenuWidget::SwitchToSettingsView()
{
	WidgetSwitcherRoot->SetActiveWidgetIndex(EMenuIndex::Settings);
}

void URootMainMenuWidget::SwitchToCreditsView()
{
	WidgetSwitcherRoot->SetActiveWidgetIndex(EMenuIndex::Credits);
}
