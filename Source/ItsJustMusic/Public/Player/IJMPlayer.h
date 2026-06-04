// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IJMPlayer.generated.h"

class UInputAction;
struct FInputActionValue;

UCLASS()
class ITSJUSTMUSIC_API AIJMPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AIJMPlayer();


protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IJM|Movement")
	float SprintSpeed = 900.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IJM|Movement")
	float WalkSpeed = 600.0f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IJM|Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;

protected:
	UFUNCTION(BlueprintCallable, Category = "IJM|Input")
	virtual void DoAim(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "IJM|Input")
	virtual void DoMove(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "IJM|Input")
	virtual void DoStartJump();

	UFUNCTION(BlueprintCallable, Category = "IJM|Input")
	virtual void DoEndJump();

	UFUNCTION(BlueprintCallable, Category = "IJM|Input")
	virtual void DoStartSprint();

	UFUNCTION(BlueprintCallable, Category = "IJM|Input")
	virtual void DoEndSprint();

	UFUNCTION(BlueprintCallable, Category = "IJM|Input")
	virtual void DoStartCrouch();

	UFUNCTION(BlueprintCallable, Category = "IJM|Input")
	virtual void DoEndCrouch();

	UPROPERTY(EditAnywhere, Category = "IJM|Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = "IJM|Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "IJM|Input")
	UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, Category = "IJM|Input")
	UInputAction* CrouchAction;
	UPROPERTY(EditAnywhere, Category = "IJM|Input")
	UInputAction* LookAction;
};
