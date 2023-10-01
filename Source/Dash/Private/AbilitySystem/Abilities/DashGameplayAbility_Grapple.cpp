// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DashGameplayAbility_Grapple.h"

void UDashGameplayAbility_Grapple::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("DashGameplayAbility"));
	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	
}

void UDashGameplayAbility_Grapple::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
