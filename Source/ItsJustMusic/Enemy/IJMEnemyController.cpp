// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/IJMEnemyController.h"
#include "Core/IJMGameInstance.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Hearing.h"
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

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->HearingRange = 3000.0f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	AIPerceptionComp->ConfigureSense(*HearingConfig);

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
	UBlackboardComponent* BB = GetBlackboardComponent();
	if(!BB)
	{
		return;
	}

	const FAISenseID SightID = UAISense::GetSenseID<UAISense_Sight>();
	const FAISenseID HearingID = UAISense::GetSenseID<UAISense_Hearing>();
	if(Stimulus.Type == SightID)
	{
		AIJMPlayer* IJMPlayer = Cast<AIJMPlayer>(Actor);
		if(!IJMPlayer)
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
	else if(Stimulus.Type == HearingID)
	{
		if(Stimulus.WasSuccessfullySensed())
		{
			BB->SetValueAsVector(TEXT("NoiseLocation"), Stimulus.StimulusLocation);
			BB->SetValueAsBool(TEXT("HeardNoise"), true);
		}
	}

}
