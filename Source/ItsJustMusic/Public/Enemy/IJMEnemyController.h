// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "IJMEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API AIJMEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AIJMEnemyController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|AI")
	TObjectPtr<class UBehaviorTree> BehaviorTreeAsset;
};
