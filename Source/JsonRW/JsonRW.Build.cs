// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class JsonRW : ModuleRules
{
	public JsonRW(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","XmlParser","Json", "JsonUtilities", "Networking","HTTP" });

        PrivateDependencyModuleNames.AddRange(new string[] { "HTTP" });
        PrivateIncludePathModuleNames.AddRange(new string[] { "HTTP" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
