// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomSplashScreen.h"
#include "Interfaces/IPluginManager.h"
#include "GenericPlatform/GenericPlatformSplash.h"

#define LOCTEXT_NAMESPACE "FCustomSplashScreenModule"

void FCustomSplashScreenModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	SetCustomSplashImage();
}

void FCustomSplashScreenModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FCustomSplashScreenModule::SetCustomSplashImage()
{
	// �v���O�C���f�B���N�g������X�v���b�V���摜�̃f�B���N�g���p�X���擾
	const FString PluginDirectory = IPluginManager::Get().FindPlugin(TEXT("CustomSplashScreen"))->GetBaseDir();
	const FString SplashImageDirectory = PluginDirectory + TEXT("/LocalSplash/");

	TArray<FString> SplashImagePaths;
	FindSplashImageFiles(SplashImageDirectory, SplashImagePaths);

	if (SplashImagePaths.Num() > 0)
	{
		// �����_���ɉ摜��I�����ăX�v���b�V���X�N���[���ɐݒ�
		const int32 RandomIndex = FMath::RandRange(0, SplashImagePaths.Num() - 1);
		FGenericPlatformSplash::SetCustomSplashImage(*SplashImagePaths[RandomIndex]);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("�X�v���b�V���摜��������܂���: %s"), *SplashImageDirectory);
	}
}

void FCustomSplashScreenModule::FindSplashImageFiles(const FString& DirectoryPath, TArray<FString>& OutImageFilePaths)
{
	// �ΏۂƂȂ�摜�g���q
	const TArray<FString> SupportedExtensions = { TEXT("bmp"), TEXT("png"), TEXT("jpg") };

	TArray<FString> FoundFiles;
	IFileManager::Get().FindFilesRecursive(FoundFiles, *DirectoryPath, TEXT("*.*"), true, false);

	// �Ώۊg���q�̂ݒ��o
	for (const auto& FilePath : FoundFiles)
	{
		const FString FileExtension = FPaths::GetExtension(FilePath).ToLower();
		if (SupportedExtensions.Contains(FileExtension))
		{
			OutImageFilePaths.Add(FilePath);
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomSplashScreenModule, CustomSplashScreen)