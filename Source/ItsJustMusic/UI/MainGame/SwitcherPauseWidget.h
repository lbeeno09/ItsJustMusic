// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SwitcherPauseWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPauseResumeRequested);

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API USwitcherPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnPauseResumeRequested OnPauseResumeRequested;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> WidgetSwitcherPause;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UPauseWidget> WBPPause;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USettingsWidget> WBPSettings;

private:
	enum EPauseIndex
	{
		Pause,
		Settings,
	};

	UFUNCTION()
	void SwitchToPauseView();
	UFUNCTION()
	void SwitchToSettingsView();
	UFUNCTION()
	void HandleResumeSignal();
};
