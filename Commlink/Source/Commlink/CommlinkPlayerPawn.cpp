// Fill out your copyright notice in the Description page of Project Settings.


#include "CommlinkPlayerPawn.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACommlinkPlayerPawn::ACommlinkPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	SetRootComponent(root);

	MinimapSphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Minimap Sphere"));
	MinimapSphereMesh->AttachTo(root);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere"));

	if (SphereMeshAsset.Succeeded())
	{
		MinimapSphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	}

	MinimapSphereMesh->SetRenderCustomDepth(1);
	MinimapSphereMesh->SetCustomDepthStencilValue(8);
	MinimapSphereMesh->SetRelativeTransform(FTransform(
		FQuat::Identity, 
		FVector::UpVector * 480.f, 
		FVector::OneVector * 4.517f));

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->AttachTo(root);
	PlayerCamera->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
}

void ACommlinkPlayerPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MinimapSphereMesh->SetMaterial(0, SphereMaterial);
}

// Called when the game starts or when spawned
void ACommlinkPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACommlinkPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACommlinkPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

