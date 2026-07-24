// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/IJMPlayer.h"
#include "Core/MainGameMode.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AISense_Hearing.h"

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

	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLight"));
	FlashLight->SetupAttachment(GetMesh());
}

void AIJMPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = BaseMoveSpeed;
	CurrentStamina = MaxStamina;
}

void AIJMPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsRunning)
	{
		UpdateStamina(-StaminaDecayRate * DeltaTime);
	}
	else
	{
		if(bCanStaminaRegenerate)
		{
			UpdateStamina(StaminaRechargeRate * DeltaTime);
		}
	}

	if(bIsPlayingMusic)
	{
		CurrentSanity = FMath::Clamp(CurrentSanity + (SanityRegenRate * DeltaTime), 0.0f, MaxSanity);

		UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), MusicLoudness, this, MusicHearRange, FName("MusicNoise"));
	}
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
		if(EscapeAction)
		{
			EnhancedInputComponent->BindAction(EscapeAction, ETriggerEvent::Triggered, this, &AIJMPlayer::Escape);
		}
		if(ListenAction)
		{
			EnhancedInputComponent->BindAction(ListenAction, ETriggerEvent::Triggered, this, &AIJMPlayer::ToggleMusic);
		}
	}
}

void AIJMPlayer::UpdateStamina(float Amount)
{
	CurrentStamina = FMath::Clamp(CurrentStamina + Amount, 0.0f, MaxStamina);

	if(CurrentStamina <= 0.0f)
	{
		bCanStaminaRegenerate = false;

		GetWorldTimerManager().ClearTimer(StaminaRegenTimerHandle);
		GetWorldTimerManager().SetTimer(StaminaRegenTimerHandle, this, &AIJMPlayer::ResetStaminaRegen, 1.0f, false);

		EndSprint();
	}

	float StaminaPercent = CurrentStamina / MaxStamina;
	OnStaminaChanged.Broadcast(StaminaPercent);
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
	if(bIsLookingBack)
	{
		return;
	}

	bIsLookingBack = true;

	FRotator ControlRotation = Controller->GetControlRotation();
	ControlRotation.Yaw += 180.0f;
	ControlRotation.Normalize();

	Controller->SetControlRotation(ControlRotation);
}

void AIJMPlayer::TurnFront()
{
	if(!bIsLookingBack)
	{
		return;
	}

	bIsLookingBack = false;

	FRotator ControlRotation = Controller->GetControlRotation();
	ControlRotation.Yaw -= 180.0f;
	ControlRotation.Normalize();

	Controller->SetControlRotation(ControlRotation);
}

void AIJMPlayer::StartSprint()
{
	bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AIJMPlayer::EndSprint()
{
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = BaseMoveSpeed;
}

void AIJMPlayer::ToggleMusic()
{
	bIsPlayingMusic = !bIsPlayingMusic;

}

void AIJMPlayer::Escape()
{
	OnEscapeInputTriggered.Broadcast();
}

void AIJMPlayer::ResetStaminaRegen()
{
	bCanStaminaRegenerate = true;
}
