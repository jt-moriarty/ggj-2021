// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommlinkAudioSourceInfo.h"
#include "GameFramework/GameMode.h"
#include "CommlinkGameMode.generated.h"

/**
 * 
 */
UCLASS()
class COMMLINK_API ACommlinkGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void SetAudioInfos(TArray<FCommlinkAudioSourceInfo> NewAudioInfos) { AudioInfos = NewAudioInfos; }

	TArray<FCommlinkAudioSourceInfo> AudioInfos;
};
