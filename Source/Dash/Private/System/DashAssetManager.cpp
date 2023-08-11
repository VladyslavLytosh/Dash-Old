// Fill out your copyright notice in the Description page of Project Settings.


#include "System/DashAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "DashGameplayTags.h"

void UDashAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	InitializeAbilitySystem();

}

void UDashAssetManager::InitializeAbilitySystem()
{
	SCOPED_BOOT_TIMING("ULyraAssetManager::InitializeAbilitySystem");
    
	FDashGameplayTags::InitializeNativeTags();
    
	UAbilitySystemGlobals::Get().InitGlobalData();
}
