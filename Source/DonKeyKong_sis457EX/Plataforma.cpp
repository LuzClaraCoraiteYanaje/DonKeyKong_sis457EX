// Fill out your copyright notice in the Description page of Project Settings.


#include "Plataforma.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APlataforma::APlataforma()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));

	MeshPlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshPlataforma->SetStaticMesh(MeshAsset.Object);
	RootComponent = MeshPlataforma;


	Speed = 100.0f;
	bMovingRight = true;

	MovementDirection = FVector(0.0f, .0f, 0.0f);
}

// Called when the game starts or when spawned
void APlataforma::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	EndLocation = StartLocation + MovementDirection * 1000.0f;
	
}

// Called every frame
void APlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);

}

void APlataforma::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector Direction = (bMovingRight ? EndLocation : StartLocation) - CurrentLocation;
	Direction.Normalize();
	CurrentLocation += Direction * Speed * DeltaTime;
	SetActorLocation(CurrentLocation);

	if (FVector::Dist(CurrentLocation, bMovingRight ? EndLocation : StartLocation) < 10.0f)
	{
		bMovingRight = !bMovingRight;
	}
}

void APlataforma::SetMovementDirection(FVector NewDirection)
{
	MovementDirection = NewDirection;
	EndLocation = StartLocation + MovementDirection * 500.0f;
}

