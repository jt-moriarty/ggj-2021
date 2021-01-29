// Fill out your copyright notice in the Description page of Project Settings.


#include "CommlinkSoundRecordingListener.h"

// Sets default values
ACommlinkSoundRecordingListener::ACommlinkSoundRecordingListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACommlinkSoundRecordingListener::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACommlinkSoundRecordingListener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

