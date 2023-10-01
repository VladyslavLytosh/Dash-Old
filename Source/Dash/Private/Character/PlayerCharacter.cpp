// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/DashAbilitySet.h"
#include "AbilitySystem/PlayerAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/DashCharacterMovementComponent.h"
#include "Character/DashHeroComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UDashCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	DashCharacterMovementComponent = Cast<UDashCharacterMovementComponent>(GetCharacterMovement());
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetMesh(),"Head");
	CameraComponent->bUsePawnControlRotation = true;

	HeroComponent = CreateDefaultSubobject<UDashHeroComponent>(TEXT("HeroComponent"));
	
	DashCharacterMovementComponent->bOrientRotationToMovement = false;

	AbilitySystemComponent = CreateDefaultSubobject<UPlayerAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	bReplicates = true;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!AbilitySystemComponent) return;
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (HasAuthority())
	{
		TryApplyAbilitySet(DefaultAbilitySet);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(HeroComponent);

	HeroComponent->InitializePlayerInput(PlayerInputComponent);
}

FCollisionQueryParams APlayerCharacter::GetIgnoreCharacterParams() const
{
	FCollisionQueryParams Params;

	TArray<AActor*> CharacterChildren;
	GetAllChildActors(CharacterChildren);
	Params.AddIgnoredActors(CharacterChildren);
	Params.AddIgnoredActor(this);

	return Params;
}

void APlayerCharacter::TryApplyAbilitySet(const UDashAbilitySet* AbilitySet, bool bCancelEarlySet)
{
	if (bCancelEarlySet)
	{
		GrantedHandles.TakeFromAbilitySystem(AbilitySystemComponent);
	}

	if (AbilitySet)
	{
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, &GrantedHandles);
	}
}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

