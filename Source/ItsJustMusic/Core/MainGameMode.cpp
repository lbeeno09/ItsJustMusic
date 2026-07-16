// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/MainGameMode.h"
#include "UI/HUD/MainGameHUD.h"
#include "Maze/OrbActor.h"
#include "Maze/MazeGenerator.h"
#include "Kismet/GameplayStatics.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	if(MazeGeneratorClass)
	{
		AActor* FoundGeneratorActor = UGameplayStatics::GetActorOfClass(GetWorld(), MazeGeneratorClass);
		if(AMazeGenerator* Generator = Cast< AMazeGenerator>(FoundGeneratorActor))
		{
			GoalPlatformActor = Generator->GenerateMaze();
		}
	}

	TArray<AActor*> FoundOrbs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOrbActor::StaticClass(), FoundOrbs);
	TotalOrb = FoundOrbs.Num();
	OnOrbCountChanged.Broadcast(TotalOrb);
}

void AMainGameMode::HandleOrbCollected()
{
	TotalOrb = FMath::Max(0, TotalOrb - 1);
	OnOrbCountChanged.Broadcast(TotalOrb);
}

void AMainGameMode::CompleteLevel()
{
	OnGoalPlatformReached.Broadcast();
}

void AMainGameMode::GameOver()
{
	OnEnemyCaptured.Broadcast();
}
