// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CommlinkHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class COMMLINK_API ACommlinkHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetCoords(const int XCoord, const int YCoord);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetVisionType(const int VisionIndex);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetAudioInfo(const FText& SourceName, const FText& SourceType);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OnMaySubmitReport();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SendMessage(const FText& Message);
};
