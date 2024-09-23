// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemigoCubo.generated.h"

UCLASS()
class DONKEYKONG_SIS457EX_API AEnemigoCubo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemigoCubo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	 class UStaticMeshComponent* MeshCubo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
