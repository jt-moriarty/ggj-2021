// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CommlinkPlayerPawn.generated.h"

UCLASS()
class COMMLINK_API ACommlinkPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACommlinkPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UMaterial* SphereMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UStaticMeshComponent* MinimapSphereMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UCameraComponent* PlayerCamera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;
};
