// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BoomInternal : ModuleRules
{
	public BoomInternal(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "PlayerMovement" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"PlayerInputController",
			"PlayerMovement",
			"CustomStateMachine",
			"CharacterInterfaces",
			"Combat"
		});
	}
}
