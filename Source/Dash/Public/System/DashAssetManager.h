// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DashAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class DASH_API UDashAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
protected:
	virtual void StartInitialLoading() override;
	
private:
	void InitializeAbilitySystem();
};
