// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainGame/GameUIWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Core/MainGame/MainGameMode.h"
#include "Player/IJMPlayer.h"
#include "Kismet/GameplayStatics.h"

void UGameUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AMainGameMode* MainGameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	AIJMPlayer* IJMPlayer = Cast<AIJMPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	MainGameMode->OnOrbCountChanged.AddDynamic(this, &UGameUIWidget::HandleOrbCountChanged);
	IJMPlayer->OnStaminaChanged.AddDynamic(this, &UGameUIWidget::HandleStaminaChanged);

	TextOrbCount->SetText(FText::AsNumber(MainGameMode->GetTotalOrb()));
}

void UGameUIWidget::HandleStaminaChanged(float NewPercent)
{
	ProgressBarStamina->SetPercent(NewPercent);
}

void UGameUIWidget::HandleOrbCountChanged(int32 RemainingOrbs)
{
	TextOrbCount->SetText(FText::AsNumber(RemainingOrbs));
}
