// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonKeyKong_sis457EXGameMode.h"
#include "DonKeyKong_sis457EXCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Plataforma.h"

ADonKeyKong_sis457EXGameMode::ADonKeyKong_sis457EXGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADonKeyKong_sis457EXGameMode::BeginPlay()
{
	Super::BeginPlay();

    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Actor Spawning"));

    // Definiciones iniciales
    FVector posicionInicial = FVector(1180.0, -419.9, 760.0);
    FRotator rotacionInicial = FRotator(0.0f, 0.0f, 5.0f);
    FTransform SpawnLocationCP;

    float incrementoAltoEntrePisos = 350.0f;
    float incrementoInicioPiso = 100.0f;
    float anchoComponentePlataforma = -500.0f;
    float mitadPlataforma = (anchoComponentePlataforma * 5.0f) / 2.0f;

    for (int npp = 0; npp < 12; npp++) {

        // Ajuste de rotación y desplazamiento
        if (npp >= 2 && npp <= 6) {
            rotacionInicial.Roll -= 5.0f;
        }

        // Cambiar la posición y rotación inicial para las plataformas 7 y superiores
        if (npp >= 7) {
            posicionInicial = FVector(1180.0, 300.0, 1030.0 + incrementoAltoEntrePisos * (npp - 7)); // Incrementa la altura para cada plataforma 7, 8, 9
            rotacionInicial = FRotator(0.0f, 0.0f, 0.0f);

            if (npp % 2 == 0) {
                posicionInicial.Y -= 400.0f; // Mover a la derecha
            }
            else {
                posicionInicial.Y += 400.0f; // Mover a la izquierda
            }

        }


        rotacionInicial.Roll *= -1;
        incrementoInicioPiso *= -1;

        SpawnLocationCP.SetRotation(FQuat(rotacionInicial));
        SpawnLocationCP.SetLocation(posicionInicial);

        // Crear la plataforma
        APlataforma* plataforma = GetWorld()->SpawnActor<APlataforma>(APlataforma::StaticClass(), SpawnLocationCP);

        if (plataforma) {
            // Configurar la escala de la plataforma
            FVector escalaPlataforma = FVector(2.5f, 18.0f, 0.5f);

            // Ajustar el tamaño de la plataforma 7
            if (npp >= 7) {
                escalaPlataforma = FVector(3.0f, 10.0f, 0.5f);

                plataforma->SetMovementDirection(FVector(0.0f, 0.0f, -1.0f));
            }
            plataforma->SetActorScale3D(escalaPlataforma);


            if (npp == 6) {
                plataforma->SetMovementDirection(FVector(0.0f, 0.0f, -1.0f)) ; 
            }

           
            if (npp == 11) {
                plataforma->SetMovementDirection(FVector(0.0f, -1.0f, 0.0f)); 
            }

            ComponentePlataformaMap.Add(npp, plataforma);
        }

        // Ajuste de posición para la siguiente plataforma
        if (npp >= 7) {
            posicionInicial.Z += incrementoAltoEntrePisos;
        }
        else {
            posicionInicial.Z += incrementoAltoEntrePisos;
            posicionInicial.Y += incrementoInicioPiso + mitadPlataforma;
        }
    }
}

void ADonKeyKong_sis457EXGameMode::Tick(float DeltaTime)
{


    Super::Tick(DeltaTime);

    for (auto& Elem : ComponentePlataformaMap)
    {
        if (Elem.Value)
        {
            Elem.Value->MovePlatform(DeltaTime);
        }
    }
}


