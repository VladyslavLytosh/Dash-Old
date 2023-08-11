// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDashInputComponent;
class UDashHeroComponent;

UCLASS(Abstract)
class DASH_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	UDashHeroComponent* HeroComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	UCameraComponent* CameraComponent;
};
