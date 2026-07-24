// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/IJMGameInstance.h"

void UIJMGameInstance::Init()
{
	Super::Init();

	bUseRL = false;
	SelectedDifficulty = EGameDifficulty::Medium;
}
