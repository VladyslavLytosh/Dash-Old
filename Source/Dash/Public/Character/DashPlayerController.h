// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DashPlayerController.generated.h"


UCLASS()
class DASH_API ADashPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

	virtual void AcknowledgePossession(APawn* P) override;
};
