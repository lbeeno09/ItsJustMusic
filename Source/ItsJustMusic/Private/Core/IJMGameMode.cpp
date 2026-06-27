// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/IJMGameMode.h"
#include "Game/OrbActor.h"
#include "Core/MazeGenerator.h"
#include "Kismet/GameplayStatics.h"

void AIJMGameMode::BeginPlay()
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
	TotalOrbRemaining = FoundOrbs.Num();

	GetWorldTimerManager().SetTimerForNextTick([this]()
	{
		OnOrbCountChanged.Broadcast(TotalOrbRemaining);
	});
}

void AIJMGameMode::RegisterOrbCollected()
{
	TotalOrbRemaining = FMath::Max(0, TotalOrbRemaining - 1);
	OnOrbCountChanged.Broadcast(TotalOrbRemaining);
	
	if(TotalOrbRemaining <= 0)
	{

	}
}

void AIJMGameMode::CompleteLevel()
{
	DisplayEndScreen(true);

	if(APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->SetShowMouseCursor(true);

		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
	}

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AIJMGameMode::GameOver()
{
	DisplayEndScreen(false);

	if(APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->SetShowMouseCursor(true);

		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
	}

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
