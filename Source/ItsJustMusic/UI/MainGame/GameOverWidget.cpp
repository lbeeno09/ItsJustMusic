// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainGame/GameOverWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonRetry->OnClicked.AddDynamic(this, &UGameOverWidget::OnButtonRetryClicked);
	ButtonTitle->OnClicked.AddDynamic(this, &UGameOverWidget::OnButtonTitleClicked);
}

void UGameOverWidget::ShowVictory()
{
	TextResult->SetText(FText::FromString("Victory!"));
}

void UGameOverWidget::ShowLoss()
{
	TextResult->SetText(FText::FromString("Game Over"));
}

void UGameOverWidget::OnButtonRetryClicked()
{
	// NOTE: Should it be Reopning the same level
	// or Resetting the map?
	FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));
}

void UGameOverWidget::OnButtonTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("L_MainMenu"));
}