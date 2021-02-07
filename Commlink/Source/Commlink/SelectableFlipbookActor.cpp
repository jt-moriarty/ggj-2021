// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectableFlipbookActor.h"
#include "Components/AudioComponent.h"
#include "CommlinkPlayerController.h"

ASelectableFlipbookActor::ASelectableFlipbookActor()
{
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Pickup Sound Maker"));
}

void ASelectableFlipbookActor::Select()
{
	if (IsClaimed) return;

	IsClaimed = true;

	ACommlinkPlayerController* PC = Cast<ACommlinkPlayerController>(GetWorld()->GetFirstPlayerController());

	if (IsCrew)
	{
		PC->CycleMusicMixIndex();
		MyAudio->Activate();
	}

	PC->AccountFind(this, IsCrew, IsAlive, SelectionEntries);
}