// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/IJMEnemy.h"
#include "Enemy/IJMEnemyController.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AIJMEnemy::AIJMEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Enemy Mesh"));
	EnemyMesh->SetupAttachment(GetMesh());

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	AIControllerClass = AIJMEnemyController::StaticClass();
}
