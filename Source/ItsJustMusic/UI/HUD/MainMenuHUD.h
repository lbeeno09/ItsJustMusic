// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Head Feed|Widget")
	TSubclassOf<class URootMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<class URootMainMenuWidget> MainMenuWidgetInstance;
};
