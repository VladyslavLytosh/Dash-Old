// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DashGameplayAbility_Grapple.h"

#include "Character/DashCharacterMovementComponent.h"
#include "Character/PlayerCharacter.h"

void UDashGameplayAbility_Grapple::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	const APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(ActorInfo->AvatarActor.Get());
	const UDashCharacterMovementComponent* DashCharacterMovementComponent = PlayerCharacter->GetCharacterMovement<UDashCharacterMovementComponent>();
	
	if (DashCharacterMovementComponent->IsGrappling())
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void UDashGameplayAbility_Grapple::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(ActorInfo->AvatarActor.Get());
	UDashCharacterMovementComponent* DashCharacterMovementComponent = PlayerCharacter->GetCharacterMovement<UDashCharacterMovementComponent>();
	
	if (!DashCharacterMovementComponent->TryGrapple())
	{
		EndAbility(Handle,ActorInfo,ActivationInfo,true,true);
		return;
	}

	PlayerCharacter->MovementModeChangedDelegate.AddDynamic(this, &ThisClass::OnMovementModeChanged);
}

void UDashGameplayAbility_Grapple::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	const auto PlayerCharacter = Cast<APlayerCharacter>(ActorInfo->AvatarActor);
	const auto DashCharacterMovementComponent = PlayerCharacter->GetCharacterMovement<UDashCharacterMovementComponent>();
	
	PlayerCharacter->MovementModeChangedDelegate.RemoveAll(this);
	
	DashCharacterMovementComponent->SetMovementMode(MOVE_Falling);
}

void UDashGameplayAbility_Grapple::OnMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode,
	uint8 PreviousCustomMode)
{
	if(PrevMovementMode == MOVE_Custom && PreviousCustomMode == CMOVE_Grapple)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}
