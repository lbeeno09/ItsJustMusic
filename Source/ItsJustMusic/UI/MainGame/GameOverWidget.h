// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ShowVictory();
	void ShowLoss();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextResult;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonRetry;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonTitle;

private:
	UFUNCTION()
	void OnButtonRetryClicked();
	UFUNCTION()
	void OnButtonTitleClicked();
};
