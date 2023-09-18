// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

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
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(HeroComponent);

	HeroComponent->InitializePlayerInput(PlayerInputComponent);
}

