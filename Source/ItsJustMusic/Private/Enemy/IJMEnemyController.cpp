// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/IJMEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"

AIJMEnemyController::AIJMEnemyController()
{
	bWantsPlayerState = true;
}

void AIJMEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(!BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Missing Behavior Tree Asset Assignment"), *GetName());
	}
}
