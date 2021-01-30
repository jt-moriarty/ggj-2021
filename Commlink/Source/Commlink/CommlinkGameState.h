// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CommlinkGameState.generated.h"

/**
 * 
 */
UCLASS()
class COMMLINK_API ACommlinkGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int CrewFound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int CargoFound;
};
