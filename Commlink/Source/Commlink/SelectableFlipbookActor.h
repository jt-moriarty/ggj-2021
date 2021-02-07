// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "SelectableFlipbookActor.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class COMMLINK_API ASelectableFlipbookActor : public APaperFlipbookActor
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable)
		void Select();

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsClaimed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsCrew;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsAlive;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		class UAudioComponent* MyAudio;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
		TArray<FText> SelectionEntries;

public:
	ASelectableFlipbookActor();
};
