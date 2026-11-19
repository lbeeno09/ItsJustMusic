// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/OrbActor.h"
#include "Character/Player/IJMPlayer.h"
#include "Game/MainGame/MainGameMode.h"
#include "Components/SphereComponent.h"

AOrbActor::AOrbActor()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(50.0f);
	CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AOrbActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(AIJMPlayer* Player = Cast<AIJMPlayer>(OtherActor))
	{
		if(AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode()))
		{
			Player->UpdateStamina(5.0f);
			GameMode->HandleOrbCollected();
		}

		Destroy();
	}
}
