// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Common/SettingsWidget.h"
#include "Components/Button.h"

void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonReturn->OnClicked.AddDynamic(this, &USettingsWidget::OnButtonReturnClicked);
}

void USettingsWidget::OnButtonReturnClicked()
{
	OnSettingsReturnClicked.Broadcast();

}
