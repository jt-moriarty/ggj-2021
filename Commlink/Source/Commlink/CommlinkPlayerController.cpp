// Fill out your copyright notice in the Description page of Project Settings.


#include "CommlinkPlayerController.h"
#include "CommlinkGameMode.h"
#include "Kismet/GameplayStatics.h"

void ACommlinkPlayerController::BeginPlay()
{
	UWorld* World = GetWorld();
	MyZoomCamera = World->SpawnActor<ASceneCapture2D>(SceneCaptureClass,ZoomCameraStartTransform);
	
	MyPawn = UGameplayStatics::GetPlayerPawn(World, 0);

	EnvironmentalListener = World->SpawnActor<ACommlinkSoundRecordingListener>(
		SoundRecordingListenerClass, FVector(0., 0., -20000.),FRotator::ZeroRotator,FActorSpawnParameters());

	ACommlinkGameMode* GameMode = Cast<ACommlinkGameMode>(World->GetAuthGameMode());

	CrewRemaining = EnvironmentalListener->RemainingAudioInfosIndices.Num();
}

void ACommlinkPlayerController::CycleRecording()
{
	RecordingIndex = (RecordingIndex + 1) % EnvironmentalListener->RemainingAudioInfosIndices.Num();
	UseRecordingIndex();
}

ACommlinkPlayerController::ACommlinkPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ACommlinkPlayerController::ReduceCrewRemaining(class AActor* ReferredActor)
{
	for (int i = 0; i < CrewRemaining; i++)
	{
		int RealIndex = EnvironmentalListener->RemainingAudioInfosIndices[i];
		FCommlinkAudioSourceInfo Info = EnvironmentalListener->AudioInfos[RealIndex];
		if (Info.ListeningActor == ReferredActor)
		{
			int CycleIndex = EnvironmentalListener->RemainingAudioInfosIndices.IndexOfByKey(i);
			EnvironmentalListener->RemainingAudioInfosIndices.RemoveAt(CycleIndex);

			CrewRemaining--;

			if (i < RecordingIndex) RecordingIndex--;

			RecordingIndex = RecordingIndex % EnvironmentalListener->RemainingAudioInfosIndices.Num();

			UseRecordingIndex();
			break;
		}

	}

	if (CrewRemaining <= 3)
	{
		OnMaySubmitReport();
	}
	
}

void ACommlinkPlayerController::UseRecordingIndex()
{
	EnvironmentalListener->SetListenIndex(RecordingIndex);

	if (false == IsListeningToRecording) return;

	SetAudioListenerOverride(nullptr, EnvironmentalListener->GetListenerLocation(RecordingIndex), FRotator::ZeroRotator);
	SetAudioUI();
}