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
UCLASS(Abstract)
class COMMLINK_API ACommlinkPlayerController : public APlayerController
{
	GENERATED_BODY()

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

		void UseRecordingIndex();

public:
	UFUNCTION(BlueprintCallable)
	void ReduceCrewRemaining(class AActor* ReferredActor);

	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetAudioUI() const;

	ACommlinkPlayerController();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnMaySubmitReport();
};
