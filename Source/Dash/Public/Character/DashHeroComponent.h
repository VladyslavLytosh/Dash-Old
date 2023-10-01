// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "DashHeroComponent.generated.h"


struct FGameplayTag;
class UInputMappingContext;
struct FInputActionValue;
class UInputConfig;

UCLASS(Blueprintable, Meta=(BlueprintSpawnableComponent))
class DASH_API UDashHeroComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	virtual void InitializePlayerInput(UInputComponent* PlayerInputComponent);
	
protected:
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_LookMouse(const FInputActionValue& InputActionValue);

	void Input_Spint_Pressed(const FInputActionValue& InputActionValue);
	void Input_Sprint_Released(const FInputActionValue& InputActionValue);

	void Input_Crouch_Pressed(const FInputActionValue& InputActionValue);
	
	void Input_Jump_Pressed(const FInputActionValue& InputActionValue);
	void Input_Jump_Released(const FInputActionValue& InputActionValue);
	
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);
private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta = (AllowPrivateAccess = true))
	UInputConfig* InputConfig;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta = (AllowPrivateAccess = true))
	UInputMappingContext* DefaultMappingContext;
};

