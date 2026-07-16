// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/IJMEnemyController.h"
#include "Core/IJMGameInstance.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Player/IJMPlayer.h"

AIJMEnemyController::AIJMEnemyController()
{
	bWantsPlayerState = true;

	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 2000.0;
	SightConfig->LoseSightRadius = 2500.0f;
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComp->ConfigureSense(*SightConfig);
	AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AIJMEnemyController::BeginPlay()
{
	Super::BeginPlay();

	AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AIJMEnemyController::OnPerceptionUpdated);
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
		}
	}
}

void AIJMEnemyController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AIJMPlayer* IJMPlayer = Cast<AIJMPlayer>(Actor);
	if(!IJMPlayer)
	{
		return;
	}
	UBlackboardComponent* BB = GetBlackboardComponent();
	if(!BB)
	{
		return;
	}

	if(Stimulus.WasSuccessfullySensed())
	{
		BB->SetValueAsObject(TEXT("TargetActor"), IJMPlayer);
		BB->ClearValue(TEXT("LastKnownLocation"));
	}
	else
	{
		BB->SetValueAsVector(TEXT("LastKnownLocation"), Stimulus.StimulusLocation);
		BB->ClearValue(TEXT("TargetActor"));
	}
}
