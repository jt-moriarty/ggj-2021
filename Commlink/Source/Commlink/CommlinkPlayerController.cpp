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

void ACommlinkPlayerController::AccountFind(class AActor* ReferredActor, bool IsCrew, bool IsAlive, TArray<FText> AttachedMessages)
{
	if (IsAlive) FoundSurvivor = true;

	if (IsCrew)
	{
		CrewRemaining--;

		for (int i = 0; i < EnvironmentalListener->RemainingAudioInfosIndices.Num(); i++)
		{
			int RealIndex = EnvironmentalListener->RemainingAudioInfosIndices[i];
			FCommlinkAudioSourceInfo Info = EnvironmentalListener->AudioInfos[RealIndex];
			if (Info.ListeningActor == ReferredActor)
			{
				EnvironmentalListener->RemainingAudioInfosIndices.RemoveAt(i);

				if (EnvironmentalListener->RemainingAudioInfosIndices.Num() > 0)
				{

					if (i < RecordingIndex) RecordingIndex--;

					RecordingIndex = RecordingIndex % EnvironmentalListener->RemainingAudioInfosIndices.Num();

					UseRecordingIndex();
				}
				else
				{
					IsListeningToRecording = false;
					ClearAudioListenerOverride();
					SetAudioUI();
				}
				break;
			}

		}

		if (CrewRemaining <= MaximumRemainingCrewForReport)
		{
			OnMaySubmitReport();
		}

		for (FText Message : AttachedMessages) SendConsoleMessage(Message);
	}
	else
	{
		CollectedCargo++;

		for (FText Message : AttachedMessages) SendConsoleMessage(Message);

		for (FSequentialMessage MessageItem : SequentialCargoMessages)
		{
			if (MessageItem.index == CollectedCargo)
			{
				for (FText Message : MessageItem.MessageLines) SendConsoleMessage(Message);
				break;
			}
		}
	}
	
}

void ACommlinkPlayerController::UseRecordingIndex()
{
	EnvironmentalListener->SetListenIndex(RecordingIndex);

	if (false == IsListeningToRecording) return;

	SetAudioListenerOverride(nullptr, EnvironmentalListener->GetListenerLocation(RecordingIndex), FRotator::ZeroRotator);
	SetAudioUI();
}