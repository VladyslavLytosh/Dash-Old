// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameplayTagContainer.h"

struct FDashGameplayTags
{
	static const FDashGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

	static FGameplayTag FindTagByString(FString TagString, bool bMatchPartialString = false);
	
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look;
	
	FGameplayTag InputTag_Sprint;
	FGameplayTag InputTag_Crouch;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Grapple;
	
protected:
	void AddAllTags(UGameplayTagsManager& Manager);
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:
	static FDashGameplayTags GameplayTags;
};
