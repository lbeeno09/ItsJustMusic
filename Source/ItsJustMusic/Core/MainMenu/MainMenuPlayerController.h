// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class UUserWidget;

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TObjectPtr<UInputMappingContext> MainMenuMappingContext;

	UFUNCTION(BlueprintCallable, Category = "Input|Input Action")
	void TogglePause();
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TObjectPtr<UInputAction> IA_Pause;

	UPROPERTY(EditDefaultsOnly, Category = "Internal|UI Setup")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenuWidgetInstance;
	bool bIsMenuOpen = false;
};
