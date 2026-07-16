// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMenuSettingsClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMenuCreditsClicked);

class UButton;

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnMenuSettingsClicked OnMenuSettingsClicked;
	FOnMenuCreditsClicked OnMenuCreditsClicked;
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonPlay;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonSettings;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonCredits;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonQuit;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCheckBox> CheckBoxRL;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UComboBoxString> ComboBoxDifficulty;

private:
	UFUNCTION()
	void OnButtonPlayClicked();
	UFUNCTION()
	void OnButtonSettingsClicked();
	UFUNCTION()
	void OnButtonCreditsClicked();
	UFUNCTION()
	void OnButtonQuitClicked();
	UFUNCTION()
	void OnCheckBoxRLStateChanged(bool bIsChecked);
};
