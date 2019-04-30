// Fill out your copyright notice in the Description page of Project Settings.


#include "CarGenAIPlayerController.h"

ACarGenAIPlayerController::ACarGenAIPlayerController() : APlayerController()
{
	//if (GEngine)
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("PLAYER CONTROLLER OK")));
}

void	ACarGenAIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("NextPopulation", IE_Pressed, this, &ACarGenAIPlayerController::NextPopulation);
}

void	ACarGenAIPlayerController::NextPopulation()
{
	ACarGenAIGameMode *gameMode;

	if (GetWorld())
	{
		gameMode = (ACarGenAIGameMode *)GetWorld()->GetAuthGameMode();
		gameMode->RemovePopulation();
		gameMode->NewGeneration();
		gameMode->SpawnPopulation();
	}
}