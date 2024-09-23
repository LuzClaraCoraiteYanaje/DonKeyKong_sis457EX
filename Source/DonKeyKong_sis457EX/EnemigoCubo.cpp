// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoCubo.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AEnemigoCubo::AEnemigoCubo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'"));
	MeshCubo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshCubo->SetStaticMesh(MeshAsset.Object);
	RootComponent = MeshCubo;

}

// Called when the game starts or when spawned
void AEnemigoCubo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemigoCubo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

