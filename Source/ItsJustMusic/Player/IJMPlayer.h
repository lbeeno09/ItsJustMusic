// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Engine/TimerHandle.h"
#include "IJMPlayer.generated.h"

class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, NewPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEscapeInputTriggered);

UCLASS(Blueprintable)
class ITSJUSTMUSIC_API AIJMPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AIJMPlayer();

	UFUNCTION(BlueprintCallable, Category = "IJM|Player")
	void UpdateStamina(float Amount);

	UPROPERTY(BlueprintAssignable, Category = "IJM|Events")
	FOnStaminaChanged OnStaminaChanged;
	UPROPERTY(BlueprintAssignable, Category = "IJM|Events")
	FOnEscapeInputTriggered OnEscapeInputTriggered;

private:
	// Overrides
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//////////////////////////////
	// Player Stats
	//////////////////////////////
	// Speed
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Player|Speed", meta = (AllowPrivateAccess = "true"))
	float BaseMoveSpeed = 500.0f;
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Player|Speed", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 900.0f;
	UPROPERTY(VisibleAnywhere, Category = "IJM|Player|Speed", meta = (AllowPrivateAccess = "true"))
	bool bIsRunning = false;

	// Stamina
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Player|Stamina", meta = (AllowPrivateAccess = "true"))
	float MaxStamina = 100.0f;
	UPROPERTY(VisibleAnywhere, Category = "IJM|Player|Stamina", meta = (AllowPrivateAccess = "true"))
	float CurrentStamina = 100.0f;
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Player|Stamina", meta = (AllowPrivateAccess = "true"))
	float StaminaDecayRate = 12.0f;
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Player|Stamina", meta = (AllowPrivateAccess = "true"))
	float StaminaRechargeRate = 10.0f;

	void ResetStaminaRegen();
	FTimerHandle StaminaRegenTimerHandle;
	bool bCanStaminaRegenerate = true;

	// Sanity
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Player|Sanity", meta = (AllowPrivateAccess = "true"))
	float MaxSanity = 100.0f;
	UPROPERTY(VisibleAnywhere, Category = "IJM|Player|Sanity", meta = (AllowPrivateAccess = "true"))
	float CurrentSanity = 100.0f;
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Player|Sanity", meta = (AllowPrivateAccess = "true"))
	float SanityRegenRate = 2.5f;
	UPROPERTY(EditDefaultsOnly, Category = "IJM|Player|Sanity", meta = (AllowPrivateAccess = "true"))
	float SanityDecayRate = 2.5f;

	// Music
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IJM|Player|Audio", meta = (AllowPrivateAccess = "true"))
	float MusicLoudness = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IJM|Player|Audio", meta = (AllowPrivateAccess = "true"))
	float MusicHearRange = 2000.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "IJM|Player|Audio", meta = (AllowPrivateAccess = "true"))
	bool bIsPlayingMusic = false;

private:
	// Components
	UPROPERTY(VisibleAnywhere, Category = "IJM|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, Category = "IJM|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpotLightComponent> FlashLight;

private:
	// Input Action Setup
	void Look(const FInputActionValue& Value);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	void Move(const FInputActionValue& Value);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	void StartSprint();
	void EndSprint();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SprintAction;

	void TurnAround();
	void TurnFront();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> TurnAction;
	bool bIsLookingBack = false;

	void Escape();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> EscapeAction;

	void ToggleMusic();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IJM|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ListenAction;
};
