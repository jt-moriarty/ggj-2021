// Fill out your copyright notice in the Description page of Project Settings.


#include "CommlinkSoundRecordingListener.h"
#include "CommlinkGameMode.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

// Sets default values
ACommlinkSoundRecordingListener::ACommlinkSoundRecordingListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UWorld* World = GetWorld();
	if (nullptr == World) return;

	ACommlinkGameMode* GameMode = Cast<ACommlinkGameMode>(World->GetAuthGameMode());

	if (GameMode == nullptr) return;
	
	for (int i = 0; i < GameMode->AudioInfos.Num(); i++)
	{
		RemainingAudioInfosIndices.Add(i);

		FCommlinkAudioSourceInfo Info = GameMode->AudioInfos[i];
		AudioInfos.Add(Info);

		if (Info.IsInWorld)
		{
			MyAudioComponents.Add(nullptr);
		}
		else
		{
			UAudioComponent* Component = NewObject<UAudioComponent>(this, TEXT("Audio Component"));
			Component->RegisterComponent();
			Component->SetSound(Info.SoundCue);
			Component->SetVolumeMultiplier(i==0?1.:0.);

			MyAudioComponents.Add(Component);
		}
	}
}

FVector ACommlinkSoundRecordingListener::GetListenerLocation(int RecordingIndex) const
{
	FCommlinkAudioSourceInfo info = AudioInfos[RemainingAudioInfosIndices[RecordingIndex]];
	if (info.IsInWorld)
	{
		return info.ListeningActor->GetActorLocation();
	}
	else
	{
		return GetActorLocation();
	}
}

void ACommlinkSoundRecordingListener::SetListenIndex(int CueIndex)
{
	for (int i = 0 ; i < MyAudioComponents.Num() ; i++)
	{
		UAudioComponent* AudioComponent = MyAudioComponents[i];

		if (NULL != AudioComponent)
		{
			AudioComponent->SetVolumeMultiplier(CueIndex == i ? 1.:0.);
		}
	}
}

