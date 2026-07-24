// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "IJMEnemyController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;

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
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|AI")
	TObjectPtr<class UBehaviorTree> BehaviorTreeAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComp;
	UPROPERTY(Transient)
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
	UPROPERTY(Transient)
	TObjectPtr<UAISenseConfig_Hearing> HearingConfig;

private:
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
