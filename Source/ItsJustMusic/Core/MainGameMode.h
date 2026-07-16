// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOrbCountChanged, int32, RemainingOrbs);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGoalPlatformReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyCaptured);

/**
 * 
 */
UCLASS(Blueprintable)	
class ITSJUSTMUSIC_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	FOnGoalPlatformReached OnGoalPlatformReached;
	FOnEnemyCaptured OnEnemyCaptured;
	UPROPERTY(BlueprintAssignable, Category = "IJM|Events")
 	FOnOrbCountChanged OnOrbCountChanged;
//
	void HandleOrbCollected();
	UFUNCTION(BlueprintCallable, Category = "IJM|Gameflow")
	void CompleteLevel();
	UFUNCTION(BlueprintCallable, Category = "IJM|Gameflow")
	void GameOver();

	UFUNCTION(BlueprintCallable, Category = "IJM|GameFlow")
	int32 GetTotalOrb() const { return TotalOrb; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "IJM|Maze")
	TSubclassOf<class AMazeGenerator> MazeGeneratorClass;

private:
	int32 TotalOrb = 0;

	UPROPERTY()
	TObjectPtr<AActor> GoalPlatformActor;
};
