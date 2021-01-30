// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CommlinkAudioSourceInfo.h"
#include "CommlinkSoundRecordingListener.generated.h"

UCLASS()
class COMMLINK_API ACommlinkSoundRecordingListener : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACommlinkSoundRecordingListener();

protected:

	TArray<class UAudioComponent*> MyAudioComponents;

public:	

	UPROPERTY(BlueprintReadWrite)
	TArray<FCommlinkAudioSourceInfo> AudioInfos;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FVector GetListenerLocation(int RecordingIndex) const;

	UFUNCTION(BlueprintCallable)
		void SetListenIndex(int CueIndex);


};
