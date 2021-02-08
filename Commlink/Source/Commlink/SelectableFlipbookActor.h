// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "Components/TimelineComponent.h"
#include "SelectableFlipbookActor.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class COMMLINK_API ASelectableFlipbookActor : public APaperFlipbookActor
{
	GENERATED_BODY()

		UFUNCTION()
		void Select();

	UFUNCTION()
		void ControlTransparency(float Input);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsClaimed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsCrew;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsAlive;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		class UAudioComponent* MyAudio;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UPaperFlipbookComponent* MyOverlayFlipbook;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
		TArray<FText> SelectionEntries;

	UFUNCTION()
		void OnBeginMouseOver(AActor* TouchedComponent);

	UFUNCTION()
		void OnEndMouseOver(AActor* TouchedComponent);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsHovered;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsMouseDown;

	UFUNCTION()
		void OnScanDown();

	UFUNCTION()
		void OnScanUp();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCurveFloat *SelectTransparencyCurve;

	FTimeline SelectTimeline;

public:
	ASelectableFlipbookActor();

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
