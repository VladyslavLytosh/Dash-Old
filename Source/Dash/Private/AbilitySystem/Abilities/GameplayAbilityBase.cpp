// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GameplayAbilityBase.h"

#include "Character/PlayerCharacter.h"

APlayerCharacter* UGameplayAbilityBase::GetCharacterFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<APlayerCharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}
