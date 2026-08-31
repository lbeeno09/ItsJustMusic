// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainGamePlayerController.generated.h"

//class UUserWidget;

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API AMainGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = "IJM|Input|Input Mappings")
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "IJM|Input|Input Actions")
	TObjectPtr<class UInputAction> IA_Escape;

	UPROPERTY(EditAnywhere, Category = "IJM|UI")
	TObjectPtr<class UUserWidget> PauseMenuWidgetInstance;

private:
	void HandleEscape();
	
	bool bIsMenuOpen = false;
};
