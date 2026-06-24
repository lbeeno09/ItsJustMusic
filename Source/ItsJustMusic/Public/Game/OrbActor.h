// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrbActor.generated.h"

UCLASS()
class ITSJUSTMUSIC_API AOrbActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AOrbActor();

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IJM|Components")
	TObjectPtr<class USphereComponent> CollisionSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IJM|Components")
	TObjectPtr<class UStaticMeshComponent> ItemMesh;
};
