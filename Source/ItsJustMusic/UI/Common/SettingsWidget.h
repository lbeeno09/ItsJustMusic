// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsReturnClicked);

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnSettingsReturnClicked OnSettingsReturnClicked;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ButtonReturn;

private:
	UFUNCTION()
	void OnButtonReturnClicked();
};
