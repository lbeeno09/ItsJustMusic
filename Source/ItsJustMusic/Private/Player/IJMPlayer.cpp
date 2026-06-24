// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/IJMPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AIJMPlayer::AIJMPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 150.0f;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
	FirstPersonCamera->bUsePawnControlRotation = true;
}

void AIJMPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void AIJMPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIJMPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Turn Around
		if(LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AIJMPlayer::Look);
		}
		if(MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AIJMPlayer::Move);
		}
		if(SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AIJMPlayer::StartSprint);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AIJMPlayer::EndSprint);
		}
		if(TurnAction)
		{
			EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Started, this, &AIJMPlayer::TurnAround);
			EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Completed, this, &AIJMPlayer::TurnFront);
		}
	}
}


void AIJMPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if(Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AIJMPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if(Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		if(bIsLookingBack)
		{
			ForwardDirection *= -1.0f;
			RightDirection *= -1.0f;
		}
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AIJMPlayer::TurnAround()
{
	bIsLookingBack = true;

	FRotator ControlRotation = Controller->GetControlRotation();
	ControlRotation.Yaw += 180.0f;
	ControlRotation.Normalize();

	Controller->SetControlRotation(ControlRotation);
}

void AIJMPlayer::TurnFront()
{
	bIsLookingBack = false;

	FRotator ControlRotation = Controller->GetControlRotation();
	ControlRotation.Yaw -= 180.0f;
	ControlRotation.Normalize();

	Controller->SetControlRotation(ControlRotation);
}

void AIJMPlayer::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AIJMPlayer::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = BaseMoveSpeed;
}
