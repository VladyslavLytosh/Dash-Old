// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/DashAbilitySet.h"
#include "PlayerCharacter.generated.h"

class UDashAbilitySet;
class UPlayerAbilitySystemComponent;
class UDashCharacterMovementComponent;
class USpringArmComponent;
class UCameraComponent;
class UDashInputComponent;
class UDashHeroComponent;

UCLASS(Abstract)
class DASH_API APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	FCollisionQueryParams GetIgnoreCharacterParams() const;

	FORCEINLINE UCameraComponent* GetCameraComponent() const { return CameraComponent; };
	
	UFUNCTION(BlueprintCallable)
	void TryApplyAbilitySet(const UDashAbilitySet* AbilitySet, bool bCancelEarlySet = false);
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay|AbiliySet")
	TObjectPtr<const UDashAbilitySet> DefaultAbilitySet;

	UPROPERTY(VisibleAnywhere)
	FAbilitySet_GrantedHandles GrantedHandles;
};
