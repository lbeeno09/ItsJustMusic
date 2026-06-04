// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IJMEnemy.generated.h"

UCLASS()
class ITSJUSTMUSIC_API AIJMEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AIJMEnemy();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IJM|Movement")
	float SprintSpeed = 900.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IJM|Movement")
	float WalkSpeed = 600.0f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IJM|Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* EnemyCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IJM|Components", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* EnemyMesh;
};
