// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalPlatform.generated.h"

class UStaticMeshComponent;

UCLASS()
class ITSJUSTMUSIC_API AGoalPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AGoalPlatform();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IJM|Goal")
	TObjectPtr<class USceneComponent> SceneRootComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IJM|Goal")
	TObjectPtr<UStaticMeshComponent> GoalPlatform;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IJM|Goal")
	TObjectPtr<UStaticMeshComponent> GoalBridge;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IJM|Goal")
	TObjectPtr<class UBoxComponent> GoalCollision;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IJM|Goal")
	TObjectPtr<UStaticMeshComponent> GoalArea;
};
