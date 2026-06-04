// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "IJMEnemyController.generated.h"

class UBehaviorTree;

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

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;
};
