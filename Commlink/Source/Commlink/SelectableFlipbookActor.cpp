// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectableFlipbookActor.h"
#include "Components/AudioComponent.h"
#include "PaperFlipbookComponent.h"
#include "CommlinkPlayerController.h"

ASelectableFlipbookActor::ASelectableFlipbookActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Pickup Sound Maker"));
	MyAudio->SetupAttachment(GetRootComponent());

	MyOverlayFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Overlay Flipbook2"));
	MyOverlayFlipbook->SetupAttachment(GetRootComponent());

	OnBeginCursorOver.AddDynamic(this, &ASelectableFlipbookActor::OnBeginMouseOver);
	OnEndCursorOver.AddDynamic(this, &ASelectableFlipbookActor::OnEndMouseOver);
}

void ASelectableFlipbookActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (MyOverlayFlipbook)
	{
		MyOverlayFlipbook->SetFlipbook(GetRenderComponent()->GetFlipbook());
	}

	if (SelectTransparencyCurve)
	{
		SelectTimeline.SetTimelineLength(2.f);
		FOnTimelineFloat TimelineTransparencyCallback;
		FOnTimelineEvent TimelineSelectCallback;

		TimelineTransparencyCallback.BindUFunction(this, FName("ControlTransparency"));
		TimelineSelectCallback.BindUFunction(this, FName("Select"));

		SelectTimeline.AddInterpFloat(SelectTransparencyCurve, TimelineTransparencyCallback);
		SelectTimeline.AddEvent(1.f, TimelineSelectCallback);
	}
}

void ASelectableFlipbookActor::BeginPlay()
{
	Super::BeginPlay();

	EnableInput(GetWorld()->GetFirstPlayerController());

	FInputActionBinding ScanDown = InputComponent->BindAction("scan", IE_Pressed, this, &ASelectableFlipbookActor::OnScanDown);
	ScanDown.bConsumeInput = false;

	FInputActionBinding ScanUp = InputComponent->BindAction("scan", IE_Released, this, &ASelectableFlipbookActor::OnScanUp);
	ScanUp.bConsumeInput = false;
}

void ASelectableFlipbookActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SelectTimeline.TickTimeline(DeltaTime);

	if (!IsClaimed)
	{
		if (IsHovered && IsMouseDown)
		{ 
			SelectTimeline.Play();
		}
		else
		{
			SelectTimeline.Reverse();
		}
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

void ASelectableFlipbookActor::ControlTransparency(float Input)
{
	FLinearColor col(1.f, 1.f, 1.f, Input);
	MyOverlayFlipbook->SetSpriteColor(col);
}

void ASelectableFlipbookActor::OnBeginMouseOver(AActor* TouchedComponent)
{
	IsHovered = true;
}

void ASelectableFlipbookActor::OnEndMouseOver(AActor* TouchedComponent)
{
	IsHovered = false;
}

void ASelectableFlipbookActor::OnScanDown()
{
	IsMouseDown = true;
}

void ASelectableFlipbookActor::OnScanUp()
{
	IsMouseDown = false;
}