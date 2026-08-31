// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IJMGameInstance.generated.h"

UENUM(BlueprintType)
enum class EGameDifficulty : uint8
{
	Easy,
	Medium,
	Hard
};

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API UIJMGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IJM|Setting")
	bool bUseRL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IJM|Setting")
	EGameDifficulty SelectedDifficulty;

protected:
	virtual void Init() override;
};
