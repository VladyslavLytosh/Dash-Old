// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DashHeroComponent.h"

#include "DashGameplayTags.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/DashCharacterMovementComponent.h"
#include "Character/PlayerCharacter.h"
#include "Input/DashInputComponent.h"

void UDashHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);
	
	const ULocalPlayer* LP = Cast<ULocalPlayer>(PC->GetLocalPlayer());
	check(LP);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	if (!InputConfig) return;

	Subsystem->AddMappingContext(DefaultMappingContext,0);
		
	const FDashGameplayTags& GameplayTags = FDashGameplayTags::Get();

	UDashInputComponent* DashIC = CastChecked<UDashInputComponent>(PlayerInputComponent);
		
	DashIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);
		
	DashIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse,false);
		
	DashIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Sprint, ETriggerEvent::Started, this, &ThisClass::Input_Spint_Pressed,false);
	DashIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Sprint, ETriggerEvent::Completed, this, &ThisClass::Input_Sprint_Released,false);
	
	DashIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Crouch, ETriggerEvent::Started, this, &ThisClass::Input_Crouch_Pressed,false);
	
	DashIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Jump, ETriggerEvent::Triggered, this, &ThisClass::Input_Jump_Pressed,false);
	DashIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Jump, ETriggerEvent::Completed, this, &ThisClass::Input_Jump_Released,false);
}

void UDashHeroComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	const auto Controller = Pawn ? Pawn->GetController() : nullptr;

	if (!Controller) return;

	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		Pawn->AddMovementInput(Pawn->GetActorRightVector(), Value.X);
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddMovementInput(Pawn->GetActorForwardVector(), Value.Y);
	}
}

void UDashHeroComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();

	if (!Pawn) return;
	
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y);
	}
}

void UDashHeroComponent::Input_Spint_Pressed(const FInputActionValue& InputActionValue)
{
	const auto PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	if (!PlayerCharacter) return;

	const auto CharacterMovementComponent = PlayerCharacter->GetCharacterMovement<UDashCharacterMovementComponent>();
	
	CharacterMovementComponent->SprintPressed();
}

void UDashHeroComponent::Input_Sprint_Released(const FInputActionValue& InputActionValue)
{
	const auto PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	if (!PlayerCharacter) return;

	const auto CharacterMovementComponent = PlayerCharacter->GetCharacterMovement<UDashCharacterMovementComponent>();

	CharacterMovementComponent->SprintReleased();
}

void UDashHeroComponent::Input_Crouch_Pressed(const FInputActionValue& InputActionValue)
{
	const auto PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	if (!PlayerCharacter) return;

	PlayerCharacter->bIsCrouched ? PlayerCharacter->UnCrouch() : PlayerCharacter->Crouch();
}

void UDashHeroComponent::Input_Jump_Pressed(const FInputActionValue& InputActionValue)
{
	const auto PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	if (!PlayerCharacter) return;

	PlayerCharacter->Jump();
}

void UDashHeroComponent::Input_Jump_Released(const FInputActionValue& InputActionValue)
{
	const auto PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	if (!PlayerCharacter) return;

	PlayerCharacter->StopJumping();
}
