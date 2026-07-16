// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/CreditsWidget.h"
#include "Components/Button.h"

void UCreditsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonReturn->OnClicked.AddDynamic(this, &UCreditsWidget::OnButtonReturnClicked);
}

void UCreditsWidget::OnButtonReturnClicked()
{
	OnCreditsReturnClicked.Broadcast();
}
