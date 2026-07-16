// Fill out your copyright notice in the Description page of Project Settings.

#include "Maze/GoalPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

AGoalPlatform::AGoalPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	RootComponent = SceneRootComponent;

	GoalPlatform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoalPlatform"));
	GoalPlatform->SetupAttachment(RootComponent);

	GoalBridge = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoalBridge"));
	GoalBridge->SetupAttachment(RootComponent);

	GoalCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("GoalCollision"));
	GoalCollision->SetupAttachment(RootComponent);

	GoalArea = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoalArea"));
	GoalArea->SetupAttachment(GoalCollision);
}

void AGoalPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

