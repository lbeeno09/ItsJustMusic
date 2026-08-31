// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/MainGame/MainGamePlayerController.h"
#include "EnhancedInputSubsystems.h"

void AMainGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	//SetInputMode(InputMode);
	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);

	if(ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if(DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void AMainGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}
