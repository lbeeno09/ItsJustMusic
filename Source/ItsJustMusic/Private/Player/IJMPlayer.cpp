// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/IJMPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AIJMPlayer::AIJMPlayer()
{
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(GetMesh(), FName("head"));

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AIJMPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AIJMPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Jump
		EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AIJMPlayer::DoStartJump);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &AIJMPlayer::DoEndJump);

		// Moving
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AIJMPlayer::DoMove);

		// Sprint
		EIC->BindAction(SprintAction, ETriggerEvent::Started, this, &AIJMPlayer::DoStartSprint);
		EIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &AIJMPlayer::DoEndSprint);

		// Crouching
		EIC->BindAction(CrouchAction, ETriggerEvent::Started, this, &AIJMPlayer::DoStartCrouch);
		EIC->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AIJMPlayer::DoEndCrouch);

		// Looking
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AIJMPlayer::DoAim);
	}
}


void AIJMPlayer::DoAim(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AIJMPlayer::DoMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementVector.X);
	AddMovementInput(GetActorRightVector(), MovementVector.Y);
}

void AIJMPlayer::DoStartJump()
{
	Jump();
}

void AIJMPlayer::DoEndJump()
{
	StopJumping();
}

void AIJMPlayer::DoStartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AIJMPlayer::DoEndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AIJMPlayer::DoStartCrouch()
{
	Crouch();
}

void AIJMPlayer::DoEndCrouch()
{
	UnCrouch();
}
