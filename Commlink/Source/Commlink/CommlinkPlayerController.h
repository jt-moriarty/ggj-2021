// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/SceneCapture2D.h"
#include "CommlinkSoundRecordingListener.h"
#include "CommlinkPlayerController.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSequentialMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> MessageLines;
};

UCLASS(Abstract)
class COMMLINK_API ACommlinkPlayerController : public APlayerController
{
	GENERATED_BODY()

	void OnHorizontal(float Amount);
	void OnVertical(float Amount);

	float movingAverageHorizontal;
	float movingAverageVertical;

	float DeltaTime;

	void ClampActorLocation();

protected:
		UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FTransform ZoomCameraStartTransform;

		UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASceneCapture2D> SceneCaptureClass;

		UPROPERTY(BlueprintReadWrite)
		ASceneCapture2D* MyZoomCamera;

		UPROPERTY(BlueprintReadWrite)
		APawn* MyPawn;

		UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ACommlinkSoundRecordingListener> SoundRecordingListenerClass;

		UPROPERTY(BlueprintReadWrite)
		class ACommlinkSoundRecordingListener* EnvironmentalListener;

		UFUNCTION(BlueprintCallable)
		void CycleRecording();

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int RecordingIndex;

		UPROPERTY(BlueprintReadWrite)
		bool IsListeningToRecording;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int CrewRemaining;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool FoundSurvivor;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MaximumRemainingCrewForReport;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int CollectedCargo;

		void UseRecordingIndex();

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FSequentialMessage> SequentialCargoMessages;

		void SendConsoleMessage(const FText& Message);

		virtual void SetupInputComponent() override;

		void UpdateCoords();

		void ToggleListenRecording();

		void QuitGame();

		class ACommlinkHUD* MyCommlinkHUD;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			FVector CoordsOffset;

		void CycleVisionMode();

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			int VisionIndex;

		UFUNCTION(BlueprintCallable)
			void SetMusicIndex(const int MixRatio);

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			int MusicMixIndex;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UAudioComponent* MyMusicPlayer;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UUserWidget> GameoverWidget;

public:
	UFUNCTION(BlueprintCallable)
	void AccountFind(class AActor* ReferredActor, bool IsCrew, bool IsAlive, TArray<FText> AttachedMessages);

	void BeginPlay() override;

	virtual void Tick(float CurrentDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetAudioUI();

	ACommlinkPlayerController();

	UFUNCTION(BlueprintCallable)
	void OnMaySubmitReport();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MoveSpeed;
	
	UFUNCTION(BlueprintCallable)
	void CycleMusicMixIndex();

	UFUNCTION(BlueprintCallable)
		void OnReportSubmitted();
};
