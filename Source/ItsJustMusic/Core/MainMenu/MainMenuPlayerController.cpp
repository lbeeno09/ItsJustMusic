// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/MainMenu/MainMenuPlayerController.h"
#include "UI/MainMenu/RootMainMenuWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(MainMenuMappingContext)
		{
			Subsystem->AddMappingContext(MainMenuMappingContext, 0);
		}
	}

	if(MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if(MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport(0);
		}
	}

	FInputModeGameAndUI InputMode;
	if(MainMenuWidgetInstance)
	{
		InputMode.SetWidgetToFocus(MainMenuWidgetInstance->TakeWidget());
	}
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetShowMouseCursor(true);
	SetInputMode(InputMode);
}

void AMainMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if(IA_Pause)
		{
			EIC->BindAction(IA_Pause, ETriggerEvent::Started, this, &AMainMenuPlayerController::TogglePause);
		}
	}
}

void AMainMenuPlayerController::TogglePause()
{
	if(URootMainMenuWidget* RootMainMenu = Cast<URootMainMenuWidget>(MainMenuWidgetInstance))
	{
		RootMainMenu->HandleEscapeAction();
	}
}
