// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/MainGameHUD.h"
#include "UI/MainGame/RootMainGameWidget.h"
#include "Blueprint/UserWidget.h"

void AMainGameHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetOwningPlayerController();
	if(MainGameWidgetClass && PC)
	{
		MainGameWidgetInstance = CreateWidget<URootMainGameWidget>(PC, MainGameWidgetClass);
		MainGameWidgetInstance->AddToViewport();

		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
		PC->SetShowMouseCursor(false);
	}
}