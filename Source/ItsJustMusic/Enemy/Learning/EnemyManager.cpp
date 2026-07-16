// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/Learning/EnemyManager.h"
#include "LearningAgentsManager.h"

AEnemyManager::AEnemyManager()
{
	PrimaryActorTick.bCanEverTick = true;

	EnemyManager = CreateDefaultSubobject<ULearningAgentsManager>(TEXT("EnemyManager"));
}

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

