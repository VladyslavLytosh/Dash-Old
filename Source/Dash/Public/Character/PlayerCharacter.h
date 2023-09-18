// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UDashCharacterMovementComponent;
class USpringArmComponent;
class UCameraComponent;
class UDashInputComponent;
class UDashHeroComponent;

UCLASS(Abstract)
class DASH_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement)
	UDashCharacterMovementComponent* DashCharacterMovementComponent;
	
private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	UDashHeroComponent* HeroComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	UCameraComponent* CameraComponent;
};
