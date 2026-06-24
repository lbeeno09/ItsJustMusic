// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/IJMEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

AIJMEnemy::AIJMEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
}
