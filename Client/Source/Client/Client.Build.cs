// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Client : ModuleRules
{
	public Client(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        //protobuf
        {
            string libPath = "Libraries/libs/protobuf/libprotobuf.lib";
            string libFullPath = System.IO.Path.Combine(Target.ProjectFile.Directory.FullName, libPath);
            PublicAdditionalLibraries.Add(libFullPath);

            string includePath = "Libraries/include";
            string includeFullPath = System.IO.Path.Combine(Target.ProjectFile.Directory.FullName, includePath);
            PublicIncludePaths.Add(includeFullPath);
        }
    }
}
