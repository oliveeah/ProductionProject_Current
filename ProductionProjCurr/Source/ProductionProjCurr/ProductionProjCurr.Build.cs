// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProductionProjCurr : ModuleRules
{
	public ProductionProjCurr(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ProductionProjCurr",
			"ProductionProjCurr/Variant_Platforming",
			"ProductionProjCurr/Variant_Combat",
			"ProductionProjCurr/Variant_Combat/AI",
			"ProductionProjCurr/Variant_SideScrolling",
			"ProductionProjCurr/Variant_SideScrolling/Gameplay",
			"ProductionProjCurr/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
