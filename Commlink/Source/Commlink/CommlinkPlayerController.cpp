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


}

void ACommlinkPlayerController::CycleRecording()
{
	RecordingIndex = (RecordingIndex + 1) % EnvironmentalListener->AudioInfos.Num();

	EnvironmentalListener->SetListenIndex(RecordingIndex);

	if (false == IsListeningToRecording) return;
	
	SetAudioListenerOverride(nullptr, EnvironmentalListener->GetListenerLocation(RecordingIndex), FRotator::ZeroRotator);
	SetAudioUI();
}

