// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/MainMenuHUD.h"
#include "UI/MainMenu/RootMainMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(MainMenuWidgetClass && PC)
	{
		MainMenuWidgetInstance = CreateWidget<URootMainMenuWidget>(PC, MainMenuWidgetClass);
		MainMenuWidgetInstance->AddToViewport(0);

		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(MainMenuWidgetInstance->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
		PC->SetShowMouseCursor(true);
	}
}