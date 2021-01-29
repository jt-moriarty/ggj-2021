// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CommlinkAudioSourceInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct COMMLINK_API FCommlinkAudioSourceInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commlink")
	bool IsInWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commlink")
	class AActor* ListeningActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commlink")
	class USoundCue* SoundCue;
};
