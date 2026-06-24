// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IJMGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOrbCountChanged, int32, RemainingOrbs);

/**
 * 
 */
UCLASS()	
class ITSJUSTMUSIC_API AIJMGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "IJM|GameFlow")
	void DisplayEndScreen(bool bPlayerWon);

	void RegisterOrbCollected();
	void GameOver();

	UPROPERTY(BlueprintAssignable, Category = "IJM|Events")
	FOnOrbCountChanged OnOrbCountChanged;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "IJM|Maze")
	TSubclassOf<class AMazeGenerator> MazeGeneratorClass;

private:
	int32 TotalOrbRemaining = 0;
};
