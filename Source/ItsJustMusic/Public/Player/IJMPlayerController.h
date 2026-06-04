// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IJMPlayerController.generated.h"

//class UUserWidget;

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API AIJMPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = "IJM|Input|Input Mappings")
	TArray<class UInputMappingContext*> DefaultMappingContexts;
};
