// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainGame/RootMainGameWidget.h"
#include "UI/MainGame/GameUIWidget.h"
#include "UI/MainGame/SwitcherPauseWidget.h"
#include "UI/MainGame/GameOverWidget.h"
#include "Core/MainGameMode.h"
#include "Player/IJMPlayer.h"
#include "Components/Overlay.h"
#include "Kismet/GameplayStatics.h"

void URootMainGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->OnGoalPlatformReached.AddDynamic(this, &URootMainGameWidget::HandleVictoryView);
		GameMode->OnEnemyCaptured.AddDynamic(this, &URootMainGameWidget::HandleLossView);
	}

	if(AIJMPlayer* Player = Cast<AIJMPlayer>(GetOwningPlayerPawn()))
	{
		Player->OnEscapeInputTriggered.AddDynamic(this, &URootMainGameWidget::HandlePauseInput);
	}

	//WBPGameUIWidget
	WBPSwitcherPause->OnPauseResumeRequested.AddDynamic(this, &URootMainGameWidget::ClosePauseMenu);
	WBPSwitcherPause->SetVisibility(ESlateVisibility::Collapsed);
	WBPGameOver->SetVisibility(ESlateVisibility::Collapsed);
}

void URootMainGameWidget::HandlePauseInput()
{
	if(bIsMenuOpen)
	{
		ClosePauseMenu();
	}
	else
	{
		bIsMenuOpen = true;
		WBPSwitcherPause->SetVisibility(ESlateVisibility::Visible);

		APlayerController* PC = GetOwningPlayer();
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(WBPSwitcherPause->TakeWidget());
		PC->SetInputMode(InputMode);
		PC->SetShowMouseCursor(true);
		PC->SetPause(true);
	}
}

void URootMainGameWidget::ClosePauseMenu()
{
	bIsMenuOpen = false;
	WBPSwitcherPause->SetVisibility(ESlateVisibility::Collapsed);

	APlayerController* PC = GetOwningPlayer();
	FInputModeGameOnly InputMode;
	PC->SetInputMode(InputMode);
	PC->SetShowMouseCursor(false);
	PC->SetPause(false);
}

void URootMainGameWidget::HandleVictoryView()
{
	WBPGameOver->SetVisibility(ESlateVisibility::Visible);
	WBPGameOver->ShowVictory();

	APlayerController* PC = GetOwningPlayer();
	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(WBPSwitcherPause->TakeWidget());
	PC->SetInputMode(InputMode);
	PC->SetShowMouseCursor(true);
	PC->SetPause(true);
}

void URootMainGameWidget::HandleLossView()
{
	WBPGameOver->SetVisibility(ESlateVisibility::Visible);
	WBPGameOver->ShowLoss();

	APlayerController* PC = GetOwningPlayer();
	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(WBPSwitcherPause->TakeWidget());
	PC->SetInputMode(InputMode);
	PC->SetShowMouseCursor(true);
	PC->SetPause(true);
}
