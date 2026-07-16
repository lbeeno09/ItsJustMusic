// Fill out your copyright notice in the Description page of Project Settings.

#include "Maze/MazeGenerator.h"
#include "Core/IJMGameInstance.h"
#include "Kismet/GameplayStatics.h"

AMazeGenerator::AMazeGenerator()
{
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

}

void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();

	if(UIJMGameInstance* GM = Cast< UIJMGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		switch(GM->SelectedDifficulty)
		{
			case EGameDifficulty::Easy:
				break;
			case EGameDifficulty::Medium:
				MazeWidth = 21;
				MazeHeight = 21;
				break;
			case EGameDifficulty::Hard:
				MazeWidth = 31;
				MazeHeight = 31;
				break;
		}
	}
}

AActor* AMazeGenerator::GenerateMaze()
{
	Grid.SetNumUninitialized(MazeWidth * MazeHeight);
	for(int32 i = 0; i < Grid.Num(); i++)
	{
		Grid[i] = EMazeCellType::Wall;
	}
	Grid[GetGridIndex(0, 0)] = EMazeCellType::Corner;
	Grid[GetGridIndex(MazeWidth - 1, 0)] = EMazeCellType::Corner;
	Grid[GetGridIndex(0, MazeHeight - 1)] = EMazeCellType::Corner;
	Grid[GetGridIndex(MazeWidth - 1, MazeHeight -1)] = EMazeCellType::Corner;

	RunDFS(1, 1);
	BraidMaze();
	Grid[GetGridIndex(0, 1)] = EMazeCellType::Floor;
	// 0: Top, 1: Left, 2: Right, 3: Bottom(ignore)
	ExitWallDirection = FMath::RandRange(0, 3);
	if(FMath::RandBool())
	{
		if(ExitWallDirection == 0)
		{
			int32 RandomY = FMath::RandRange(1, MazeHeight - 2);
			ExitCellCoord = FIntPoint(MazeWidth - 1, RandomY);

			Grid[GetGridIndex(MazeWidth - 1, RandomY)] = EMazeCellType::Floor;
		}
		else if(ExitWallDirection == 1)
		{
			int32 RandomX = FMath::RandRange(1, MazeWidth - 2);
			ExitCellCoord = FIntPoint(RandomX, 0);

			Grid[GetGridIndex(RandomX, 0)] = EMazeCellType::Floor;
		}
		else if(ExitWallDirection == 2)
		{
			int32 RandomX = FMath::RandRange(1, MazeWidth - 2);
			ExitCellCoord = FIntPoint(RandomX, MazeHeight - 1);

			Grid[GetGridIndex(RandomX, MazeHeight - 1)] = EMazeCellType::Floor;
		}
		else if(ExitWallDirection == 3)
		{
			// Use the same opening as 
			ExitCellCoord = FIntPoint(0, 1);
		}
	}
	SpawnWorldGeometry();
	SpawnOrbs();
	AActor* SpawnedGoal = SpawnGoalPlatform();
	SpawnChasingEnemy();

	return SpawnedGoal;
}

void AMazeGenerator::RunDFS(int32 StartX, int32 StartY)
{
	TArray<FIntPoint> CellStack;
	Grid[GetGridIndex(StartX, StartY)] = EMazeCellType::Floor;
	CellStack.Push(FIntPoint(StartX, StartY));

	while(CellStack.Num() > 0)
	{
		FIntPoint Current = CellStack.Last();
		TArray<FIntPoint> Neighbors = GetUnivisitedNeighbors(Current.X, Current.Y);

		if(Neighbors.Num() > 0)
		{
			FIntPoint Chosen = Neighbors[FMath::RandRange(0, Neighbors.Num() - 1)];

			int32 WallX = Current.X + (Chosen.X - Current.X) / 2;
			int32 WallY = Current.Y + (Chosen.Y - Current.Y) / 2;
			Grid[GetGridIndex(WallX, WallY)] = EMazeCellType::Floor;
			Grid[GetGridIndex(Chosen.X, Chosen.Y)] = EMazeCellType::Floor;

			CellStack.Push(Chosen);
		}
		else
		{
			CellStack.Pop();
		}
	}
}

void AMazeGenerator::BraidMaze()
{
	for(int32 X = 0; X < MazeWidth - 1; X++)
	{
		for(int32 Y = 0; Y < MazeHeight - 1; Y++)
		{
			if(Grid[GetGridIndex(X, Y)] != EMazeCellType::Floor)
			{
				continue;
			}

			TArray<FIntPoint> RemovableWalls;
			FIntPoint Directions[] = { FIntPoint(0, 1), FIntPoint(0, -1), FIntPoint(1, 0), FIntPoint(-1, 0) };

			for(const FIntPoint& Dir : Directions)
			{
				int32 NX = X + Dir.X;
				int32 NY = Y + Dir.Y;

				if(0 < NX && NX < MazeWidth - 1 && 0 < NY && NY < MazeHeight - 1)
				{
					if(Grid[GetGridIndex(NX, NY)] == EMazeCellType::Wall)
					{
						RemovableWalls.Add(FIntPoint(NX, NY));
					}
				}
			}

			if(RemovableWalls.Num() == 3)
			{
				FIntPoint ChosenWall = RemovableWalls[FMath::RandRange(0, 2)];
				Grid[GetGridIndex(ChosenWall.X, ChosenWall.Y)] = EMazeCellType::Floor;
			}
		}
	}
}

TArray<FIntPoint> AMazeGenerator::GetUnivisitedNeighbors(int32 X, int32 Y)
{
	TArray<FIntPoint> Neighbors;
	FIntPoint Directions[] = { FIntPoint(0, 2), FIntPoint(0, -2), FIntPoint(2, 0), FIntPoint(-2, 0) };

	for(const FIntPoint& Dir : Directions)
	{
		int32 NX = X + Dir.X;
		int32 NY = Y + Dir.Y;

		if(0 < NX && NX < MazeWidth - 1 && 0 < NY && NY < MazeHeight - 1)
		{
			if(Grid[GetGridIndex(NX, NY)] == EMazeCellType::Wall)
			{
				Neighbors.Add(FIntPoint(NX, NY));
			}
		}
	}

	return Neighbors;
}

void AMazeGenerator::SpawnWorldGeometry()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector ActorOrigin = GetActorLocation();

	float HalfWidthOffset = 0.5f * CellSize;
	float HalfHeightOffset = 0.5f * CellSize;
	for(int32 X = 0; X < MazeWidth; X++)
	{
		for(int32 Y = 0; Y < MazeHeight; Y++)
		{
			FVector LocalOffset = FVector(X * CellSize + HalfWidthOffset, Y * CellSize + HalfHeightOffset, 0.0f);
			FVector SpawnPos = ActorOrigin + LocalOffset;
			EMazeCellType Cell = Grid[GetGridIndex(X, Y)];

			if(Cell == EMazeCellType::Corner && CornerClass)
			{
				FRotator CornerRotation = FRotator::ZeroRotator;
				if(X == 0 && Y == 0)
				{
					//FRotator CornerRotation = FRotator::ZeroRotator;
				}
				else if(X == 0 && Y == MazeHeight - 1)
				{
					CornerRotation = FRotator(0.0f, -90.0f, 0.0f);
				}
				else if(X == MazeWidth - 1 && Y == 0)
				{
					CornerRotation = FRotator(0.0f, 90.0f, 0.0f);
				}
				else if(X == MazeWidth - 1 && Y == MazeHeight - 1)
				{
					CornerRotation = FRotator(0.0f, 180.0f, 0.0f);
				}

				GetWorld()->SpawnActor<AActor>(CornerClass, SpawnPos, CornerRotation, SpawnParams);
			}
			else if(Cell == EMazeCellType::Wall && WallClass)
			{
				FRotator WallRotation = FRotator::ZeroRotator;
				if(Y == 0)
				{

				}
				else if(Y == MazeHeight - 1)
				{
					WallRotation = FRotator(0.0f, 180.0f, 0.0f);
				}
				else if(X == 0)
				{
					WallRotation = FRotator(0.0f, 270.0f, 0.0f);
				}
				else if(X == MazeWidth - 1)
				{
					WallRotation = FRotator(0.0f, 90.0f, 0.0f);
				}
				else
				{
					bool bFloorToLeftOrRight = (Grid[GetGridIndex(X - 1, Y)] == EMazeCellType::Floor || Grid[GetGridIndex(X + 1, Y)] == EMazeCellType::Floor);
					if(bFloorToLeftOrRight)
					{
						WallRotation = FRotator(0.0f, 90.0f, 0.0f);
					}
				}

				GetWorld()->SpawnActor<AActor>(WallClass, SpawnPos, WallRotation, SpawnParams);
			}
			else if(Cell == EMazeCellType::Floor && FloorClass)
			{
				GetWorld()->SpawnActor<AActor>(FloorClass, SpawnPos, FRotator::ZeroRotator, SpawnParams);
			}
		}
	}
}

void AMazeGenerator::SpawnOrbs()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector ActorOrigin = GetActorLocation();
	float HalfWidthOffset = 0.5f * CellSize;
	float HalfHeightOffset = 0.5f * CellSize;

	for(int32 X = 0; X < MazeWidth; X++)
	{
		for(int32 Y = 0; Y < MazeHeight; Y++)
		{
			if(GetGridIndex(X, Y) % 2 == 0)
			{
				continue;
			}

			FVector LocalOffset = FVector(X * CellSize + HalfWidthOffset, Y * CellSize + HalfHeightOffset, 0.0f);
			FVector SpawnPos = ActorOrigin + LocalOffset;
			EMazeCellType Cell = Grid[GetGridIndex(X, Y)];

			if(OrbClass)
			{
				FVector OrbPos = SpawnPos + FVector(0.0f, 0.0f, 50.0f);
				GetWorld()->SpawnActor<AActor>(OrbClass, OrbPos, FRotator::ZeroRotator, SpawnParams);
			}
		}
	}
}


AActor* AMazeGenerator::SpawnGoalPlatform()
{
	if(!GoalPlatformClass)
	{
		return nullptr;
	}

	FVector ActorOrigin = GetActorLocation();
	const float HalfCell = CellSize * 0.5f;

	FVector ExitTileCenter;
	FVector GoalSpawnLocation;
	FRotator GoalRotation = FRotator::ZeroRotator;
	if(ExitWallDirection == 0)
	{
		ExitTileCenter = ActorOrigin + FVector((ExitCellCoord.X + 1) * CellSize, ExitCellCoord.Y * CellSize, 0.0f);
		GoalSpawnLocation = ExitTileCenter + FVector(0.0f, HalfCell, 0.0f);
	}
	else if(ExitWallDirection == 1)
	{
		ExitTileCenter = ActorOrigin + FVector(ExitCellCoord.X * CellSize, ExitCellCoord.Y * CellSize, 0.0f);
		GoalSpawnLocation = ExitTileCenter + FVector(HalfCell, 0.0f, 0.0f);
		GoalRotation = FRotator(0.0f, -90.0f, 0.0f);
	}
	else if(ExitWallDirection == 2)
	{
		ExitTileCenter = ActorOrigin + FVector(ExitCellCoord.X * CellSize, (ExitCellCoord.Y + 1) * CellSize, 0.0f);
		GoalSpawnLocation = ExitTileCenter + FVector(HalfCell, 0.0f, 0.0f);
		GoalRotation = FRotator(0.0f, 90.0f, 0.0f);
	}
	else if(ExitWallDirection == 3)
	{
		ExitTileCenter = ActorOrigin + FVector(ExitCellCoord.X * CellSize, (ExitCellCoord.Y + 1) * CellSize, 0.0f);
		GoalSpawnLocation = ExitTileCenter + FVector(0.0f, HalfCell, 0.0f);
		GoalRotation = FRotator(0.0f, 180.0f, 0.0f);
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return GetWorld()->SpawnActor<AActor>(GoalPlatformClass, GoalSpawnLocation, GoalRotation, SpawnParams);
}

void AMazeGenerator::SpawnChasingEnemy()
{
	if(!EnemyClass)
	{
		return;
	}

	FVector ActorOrigin = GetActorLocation();
	const float HalfCell = CellSize * 0.5f;

	FVector EnemySpawnLoc = ActorOrigin + FVector((MazeWidth - 1) * CellSize + HalfCell, (MazeHeight - 1) * CellSize + HalfCell, 50.0f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	APawn* SpawnedEnemy = GetWorld()->SpawnActor<APawn>(EnemyClass, EnemySpawnLoc, FRotator(0.0f, -135.0f, 0.0f), SpawnParams);
}
