// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "IJMPlayer.generated.h"

class UInputAction;

UCLASS()
class ITSJUSTMUSIC_API AIJMPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AIJMPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Input Actions
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|Input")
	TObjectPtr<UInputAction> TurnAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|Input")
	TObjectPtr<UInputAction> SprintAction;

	// Gameplay Stats
	// Plaeyer Speed
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Config")
	float SprintSpeed = 900.0f;

	// Speed FOV
	float TargetFOV = 90.0f;
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Config|Camera")
	float NormalFOV = 90.0f;
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Config|Camera")
	float SpicyFOV = 105.0f;
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Config|Camera")
	float FOVInterpSpeed = 7.0f;

private:
	UPROPERTY(VisibleAnywhere, Category = "IJM|Components")
	TObjectPtr<class UCameraComponent> FirstPersonCamera;

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void TurnAround();
	void TurnFront();
	void StartSprint();
	void EndSprint();

	bool bIsLookingBack = false;
	float BaseMoveSpeed = 600.0f;
};
