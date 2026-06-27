// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

UENUM(BlueprintType)
enum class EMazeCellType : uint8
{
	Wall,
	Floor,
	Corner
};

UCLASS()
class ITSJUSTMUSIC_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:
	AMazeGenerator();
	AActor* GenerateMaze();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IJM|Config")
	int32 MazeWidth = 11;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IJM|Config")
	int32 MazeHeight = 11;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IJM|Config")
	int32 CellSize = 400.0f;
	UPROPERTY(EditAnywhere, Category = "IJM|Config", meta = (ClampMin = "0.0", ClampMAX = "1.0"))
	float BraidIntensity = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = "IJM")
	TObjectPtr<class USceneComponent> RootSceneComponent;
	UPROPERTY(EditAnywhere, Category = "IJM|Assets")
	TSubclassOf<AActor> WallClass;
	UPROPERTY(EditAnywhere, Category = "IJM|Assets")
	TSubclassOf<AActor> FloorClass;
	UPROPERTY(EditAnywhere, Category = "IJM|Assets")
	TSubclassOf<AActor> CornerClass;
	UPROPERTY(EditAnywhere, Category = "IJM|Assets")
	TSubclassOf<AActor> OrbClass;
	UPROPERTY(EditAnywhere, Category = "IJM|Assets")
	TSubclassOf<AActor> GoalPlatformClass;
	UPROPERTY(EditAnywhere, Category = "IJM|Assets")
	TSubclassOf<APawn> EnemyClass;

	FIntPoint ExitCellCoord;
	int32 ExitWallDirection; // 0: Top, 1: Left, 2: Right, 3: Bottom

private:
	TArray<EMazeCellType> Grid;

	int32 GetGridIndex(int32 X, int32 Y) const { return X + (Y * MazeWidth); }
	void RunDFS(int32 StartX, int32 StartY);
	void BraidMaze();
	TArray<FIntPoint> GetUnivisitedNeighbors(int32 X, int32 Y);
	UFUNCTION()
	void SpawnWorldGeometry();
	AActor* SpawnGoalPlatform();
	void SpawnChasingEnemy();
};
