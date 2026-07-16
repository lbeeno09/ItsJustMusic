// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "IJMPlayer.generated.h"

class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, NewPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEscapeInputTriggered);

UCLASS()
class ITSJUSTMUSIC_API AIJMPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AIJMPlayer();

	void UpdateStamina(float Amount);

	UPROPERTY(BlueprintAssignable, Category = "IJM|Events")
	FOnStaminaChanged OnStaminaChanged;
	FOnEscapeInputTriggered OnEscapeInputTriggered;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|Input")
	TObjectPtr<UInputAction> EscapeAction;

	// Gameplay Stats
	// Plaeyer Speed
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Config")
	float SprintSpeed = 900.0f;
	UPROPERTY(VisibleAnywhere, Category = "IJM|Components")
	float CurrentStamina = 100.0f;
	UPROPERTY(VisibleAnywhere, Category = "IJM|Components")
	float StaminaDecayRate = 12.0f;
	UPROPERTY(VisibleAnywhere, Category = "IJM|Components")
	float StaminaRechargeRate = 10.0f;

private:
	UPROPERTY(VisibleAnywhere, Category = "IJM|Components")
	TObjectPtr<class UCameraComponent> FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, Category = "IJM|Components")
	TObjectPtr<class USpotLightComponent> FlashLight;

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void TurnAround();
	void TurnFront();
	void StartSprint();
	void EndSprint();
	void Escape();

	bool bIsLookingBack = false;
	bool bIsRunning = false;
	float BaseMoveSpeed = 600.0f;
	float BaseStamina = 100.0f;
};
