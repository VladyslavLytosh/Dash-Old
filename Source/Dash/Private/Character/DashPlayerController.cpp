// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DashPlayerController.h"

#include "AbilitySystem/PlayerAbilitySystemComponent.h"
#include "Character/PlayerCharacter.h"

void ADashPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);
	
	const APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacter) return;
	
	if (UPlayerAbilitySystemComponent* AbilitySystemComponent = Cast<UPlayerAbilitySystemComponent>(PlayerCharacter->GetAbilitySystemComponent()))
	{
		AbilitySystemComponent->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
}

void ADashPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	const auto PlayerCharacter = Cast<APlayerCharacter>(P);
	
	if (!PlayerCharacter->GetAbilitySystemComponent()) return;
	PlayerCharacter->GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
}
