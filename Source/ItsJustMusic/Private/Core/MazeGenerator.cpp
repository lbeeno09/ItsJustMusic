// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/MazeGenerator.h"

AMazeGenerator::AMazeGenerator()
{
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;
}

void AMazeGenerator::GenerateMaze()
{
	Grid.SetNumUninitialized(MazeWidth * MazeHeight);
	for(int32 i = 0; i < Grid.Num(); i++)
	{
		Grid[i] = EMazeCellType::Wall;
	}

	RunDFS(1, 1);
	BraidMaze();
	Grid[GetGridIndex(0, 1)] = EMazeCellType::Floor;
	// 0: Top, 1: Left, 2: Right, 3: Bottom(ignore)
	int32 ExitEdgeChoice = FMath::RandRange(0, 3);
	if(FMath::RandBool())
	{
		if(ExitEdgeChoice == 0)
		{
			Grid[GetGridIndex(MazeWidth - 1, FMath::RandRange(1, MazeHeight - 2))] = EMazeCellType::Floor;
		}
		else if(ExitEdgeChoice == 1)
		{
			Grid[GetGridIndex(FMath::RandRange(1, MazeWidth - 2), 0)] = EMazeCellType::Floor;
		}
		else
		{
			Grid[GetGridIndex(FMath::RandRange(1, MazeWidth - 2), MazeHeight - 1)] = EMazeCellType::Floor;
		}
	}
	SpawnWorldGeometry();
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
				if(FMath::FRand() <= BraidIntensity)
				{
					FIntPoint ChosenWall = RemovableWalls[FMath::RandRange(0, 2)];
					Grid[GetGridIndex(ChosenWall.X, ChosenWall.Y)] = EMazeCellType::Floor;
				}
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

			if(Cell == EMazeCellType::Wall && WallClass)
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

				// Populate with orbs

				if(OrbClass && (X != 1 || Y != 1))
				{
					FVector OrbPos = SpawnPos + FVector(0.0f, 0.0f, 50.0f);
					GetWorld()->SpawnActor<AActor>(OrbClass, OrbPos, FRotator::ZeroRotator, SpawnParams);
				}
			}
		}
	}
}
