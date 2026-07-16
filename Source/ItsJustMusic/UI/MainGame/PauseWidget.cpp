// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainGame/PauseWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonResume->OnClicked.AddDynamic(this, &UPauseWidget::OnButtonResumeClicked);
	ButtonSettings->OnClicked.AddDynamic(this, &UPauseWidget::OnButtonSettingsClicked);
	ButtonQuit->OnClicked.AddDynamic(this, &UPauseWidget::OnButtonQuitClicked);
}

void UPauseWidget::OnButtonResumeClicked()
{
	OnPauseResumeClicked.Broadcast();
}

void UPauseWidget::OnButtonSettingsClicked()
{
	OnPauseSettingsClicked.Broadcast();
}

void UPauseWidget::OnButtonQuitClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("L_MainMenu"));
}
