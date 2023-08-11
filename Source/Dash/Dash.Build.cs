// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Dash : ModuleRules
{
	public Dash(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"Dash"
			}
		);
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{			
			"InputCore",
			"GameplayTags", 
			"GameplayAbilities",
			"EnhancedInput",	
			"ModularGameplay"
		});
		


		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
