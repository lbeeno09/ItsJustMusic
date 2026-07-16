// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RootMainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API URootMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> WidgetSwitcherRoot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UMainMenuWidget> WBPMainMenu;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USettingsWidget> WBPSettings;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCreditsWidget> WBPCredits;

private:
	enum EMenuIndex
	{
		MainMenu,
		Settings,
		Credits
	};

	UFUNCTION()
	void SwitchToMainMenuView();
	UFUNCTION()
	void SwitchToSettingsView();
	UFUNCTION()
	void SwitchToCreditsView();
};
