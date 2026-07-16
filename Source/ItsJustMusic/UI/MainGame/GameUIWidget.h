// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API UGameUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ProgressBarStamina;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextOrbCount;

private:
	UFUNCTION()
	void HandleStaminaChanged(float NewPercent);
	UFUNCTION()
	void HandleOrbCountChanged(int32 RemainingOrbs);
};
