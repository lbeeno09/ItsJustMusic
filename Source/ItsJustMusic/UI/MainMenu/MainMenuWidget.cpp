// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenu/MainMenuWidget.h"
#include "Core/Common/IJMGameInstance.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonPlay->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnButtonPlayClicked);
	ButtonSettings->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnButtonSettingsClicked);
	ButtonCredits->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnButtonCreditsClicked);
	ButtonQuit->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnButtonQuitClicked);
	CheckBoxRL->OnCheckStateChanged.AddDynamic(this, &UMainMenuWidget::OnCheckBoxRLStateChanged);

	UEnum* DifficultyEnum = StaticEnum<EGameDifficulty>();
	UIJMGameInstance* GI = Cast<UIJMGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	for(int32 i = 0; i < DifficultyEnum->NumEnums() - 1; i++)
	{
		FString EnumStringName = DifficultyEnum->GetNameStringByIndex(i);
		ComboBoxDifficulty->AddOption(EnumStringName);
	}
	FString DefaultDifficulty = DifficultyEnum->GetNameStringByIndex((int32)GI->SelectedDifficulty);
	ComboBoxDifficulty->SetSelectedOption(DefaultDifficulty);

	CheckBoxRL->SetIsChecked(false);
}

void UMainMenuWidget::OnButtonPlayClicked()
{
	UEnum* DifficultyEnum = StaticEnum<EGameDifficulty>();
	UIJMGameInstance* GI = Cast<UIJMGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	FString SelectedDifficulty = ComboBoxDifficulty->GetSelectedOption();
	int32 EnumValue = DifficultyEnum->GetValueByNameString(SelectedDifficulty);

	GI->SelectedDifficulty = static_cast<EGameDifficulty>(EnumValue);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("L_FlatMap"));
}

void UMainMenuWidget::OnButtonSettingsClicked()
{
	OnMenuSettingsClicked.Broadcast();
}

void UMainMenuWidget::OnButtonCreditsClicked()
{
	OnMenuCreditsClicked.Broadcast();
}

void UMainMenuWidget::OnButtonQuitClicked()
{
	if(APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
	}
}

void UMainMenuWidget::OnCheckBoxRLStateChanged(bool bIsChecked)
{
	if(UIJMGameInstance* GameInstance = Cast<UIJMGameInstance>(GetGameInstance()))
	{
		GameInstance->bUseRL = bIsChecked;
	}
}
