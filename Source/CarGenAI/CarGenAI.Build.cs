// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CarGenAI : ModuleRules
{
	public CarGenAI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "PhysXVehicles", "HeadMountedDisplay" });

		PublicIncludePaths.Add("../ThirdParty/libvnn/includes");
		PublicLibraryPaths.Add("../ThirdParty/libvnn");
		PublicAdditionalLibraries.Add("../ThirdParty/libvnn/libvnn.so");

		PublicDefinitions.Add("HMD_MODULE_INCLUDED=1");
	}
}
