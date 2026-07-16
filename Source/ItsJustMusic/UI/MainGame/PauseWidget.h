// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPauseResumeClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPauseSettingsClicked);

class UButton;

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnPauseResumeClicked OnPauseResumeClicked;
	FOnPauseSettingsClicked OnPauseSettingsClicked;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonResume;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonSettings;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonQuit;

private:
	UFUNCTION()
	void OnButtonResumeClicked();
	UFUNCTION()
	void OnButtonSettingsClicked();
	UFUNCTION()
	void OnButtonQuitClicked();

};
