// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectableFlipbookActor.h"
#include "Components/AudioComponent.h"
#include "PaperFlipbookComponent.h"
#include "CommlinkPlayerController.h"

ASelectableFlipbookActor::ASelectableFlipbookActor()
{
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Pickup Sound Maker"));
	MyAudio->SetupAttachment(GetRootComponent());

	MyOverlayFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Overlay Flipbook2"));
	MyOverlayFlipbook->SetupAttachment(GetRootComponent());

}

void ASelectableFlipbookActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (MyOverlayFlipbook)
	{
		MyOverlayFlipbook->SetFlipbook(GetRenderComponent()->GetFlipbook());
	}
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