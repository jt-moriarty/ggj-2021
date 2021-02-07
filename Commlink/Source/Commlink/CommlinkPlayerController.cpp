// Fill out your copyright notice in the Description page of Project Settings.


#include "CommlinkPlayerController.h"
#include "CommlinkGameMode.h"
#include "CommlinkHUD.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void ACommlinkPlayerController::BeginPlay()
{
	VisionIndex = 2;
	SetMusicIndex(0);

	UWorld* World = GetWorld();
	MyZoomCamera = World->SpawnActor<ASceneCapture2D>(SceneCaptureClass,ZoomCameraStartTransform);
	
	MyPawn = UGameplayStatics::GetPlayerPawn(World, 0);

	EnvironmentalListener = World->SpawnActor<ACommlinkSoundRecordingListener>(
		SoundRecordingListenerClass, FVector(0., 0., -20000.),FRotator::ZeroRotator,FActorSpawnParameters());

	//ACommlinkGameMode* GameMode = Cast<ACommlinkGameMode>(World->GetAuthGameMode());

	MyCommlinkHUD = Cast<ACommlinkHUD>(MyHUD);
}

void ACommlinkPlayerController::CycleRecording()
{
	if (EnvironmentalListener->RemainingAudioInfosIndices.Num() > 0)
	{
		RecordingIndex = (RecordingIndex + 1) % EnvironmentalListener->RemainingAudioInfosIndices.Num();
		UseRecordingIndex();
	}
}

ACommlinkPlayerController::ACommlinkPlayerController() : APlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	MoveSpeed = 2000.f;

	MyMusicPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("My Music Player"));
}

void ACommlinkPlayerController::Tick(float CurrentDeltaTime)
{
	Super::Tick(CurrentDeltaTime);

	DeltaTime = CurrentDeltaTime;
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

void ACommlinkPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Horizontal", this, &ACommlinkPlayerController::OnHorizontal);
	InputComponent->BindAxis("Vertical", this, &ACommlinkPlayerController::OnVertical);
	InputComponent->BindAction("Toggle Listen Recording", EInputEvent::IE_Pressed, this, &ACommlinkPlayerController::ToggleListenRecording);
	InputComponent->BindAction("Cycle Recording", EInputEvent::IE_Pressed, this, &ACommlinkPlayerController::CycleRecording);
	InputComponent->BindAction("Quit Game", EInputEvent::IE_Pressed, this, &ACommlinkPlayerController::QuitGame);
	InputComponent->BindAction("Cycle Vision Mode", EInputEvent::IE_Pressed, this, &ACommlinkPlayerController::CycleVisionMode);
}

void ACommlinkPlayerController::OnHorizontal(float Amount)
{
	if (   (Amount >= 0 && movingAverageHorizontal < 0)
		|| (Amount <= 0 && movingAverageHorizontal > 0))
	{
		movingAverageHorizontal = 0;
	}

	movingAverageHorizontal = 0.99f * movingAverageHorizontal + 0.01f * (Amount * DeltaTime * MoveSpeed);

	MyPawn->AddActorWorldOffset(FVector::RightVector * movingAverageHorizontal, true); 
	ClampActorLocation();
	UpdateCoords();
}

void ACommlinkPlayerController::OnVertical(float Amount)
{
	if (   (Amount >= 0 && movingAverageVertical < 0)
		|| (Amount <= 0 && movingAverageVertical > 0))
	{
		movingAverageVertical = 0;
	}

	movingAverageVertical = 0.99f * movingAverageVertical + 0.01f * (Amount * DeltaTime * MoveSpeed);

	MyPawn->AddActorWorldOffset(FVector::ForwardVector * movingAverageVertical, true);
	ClampActorLocation();
	UpdateCoords();
}

void ACommlinkPlayerController::ClampActorLocation()
{
	FVector PrevLoc = MyPawn->GetActorLocation();
	FVector NewLoc(
		FMath::Clamp(PrevLoc.X, -3800.f, 3800.f),
		FMath::Clamp(PrevLoc.Y, -3800.f, 3800.f),
		PrevLoc.Z);
	MyPawn->SetActorLocation(NewLoc);
}

void ACommlinkPlayerController::ToggleListenRecording()
{
	if (IsListeningToRecording)
	{
		IsListeningToRecording = false;
		ClearAudioListenerOverride();
		SetAudioUI();
	}
	else if (EnvironmentalListener->RemainingAudioInfosIndices.Num() > 0)
	{
		IsListeningToRecording = true;
		UseRecordingIndex();
	}
}

void ACommlinkPlayerController::QuitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}

void ACommlinkPlayerController::UpdateCoords()
{
	FVector DisplayCoords = MyPawn->GetActorLocation() * 0.2f + CoordsOffset;

	MyCommlinkHUD->SetCoords(FMath::RoundHalfFromZero(DisplayCoords.Y), FMath::RoundHalfFromZero(DisplayCoords.X));
}

void ACommlinkPlayerController::CycleVisionMode()
{
	VisionIndex = (VisionIndex + 1) % 3;

	MyCommlinkHUD->SetVisionType(VisionIndex);
}

void ACommlinkPlayerController::CycleMusicMixIndex()
{
	MusicMixIndex = (MusicMixIndex + 1) % 9;
	SetMusicIndex(MusicMixIndex);
}

void ACommlinkPlayerController::SetMusicIndex(int MixRatio)
{
	MyMusicPlayer->SetFloatParameter("MixParam", 0.1f * MixRatio);
}