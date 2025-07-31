// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FCustomSplashScreenModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	void SetCustomSplashImage();

	void FindSplashImageFiles(const FString& DirectoryPath, TArray<FString>& OutImageFilePaths);
};
