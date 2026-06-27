// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/IJMEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Core/IJMGameInstance.h"

AIJMEnemyController::AIJMEnemyController()
{
	bWantsPlayerState = true;
}

void AIJMEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}
	else if(UIJMGameInstance* GI = Cast<UIJMGameInstance>(GetGameInstance()))
	{
		if(GI->bUseRL)
		{
			// Use RL Method
		}
	}
}
