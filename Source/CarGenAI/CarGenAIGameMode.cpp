// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CarGenAIGameMode.h"
#include "CarGenAIPlayerController.h"
#include "CarGenAIPawn.h"
#include "CarGenAIHud.h"
#include "EngineUtils.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

vyn::neuralnetwork::Network	*CreateNeuralNetwork()
{
	vyn::neuralnetwork::Network		*network;

	network = new vyn::neuralnetwork::Network;
	network->AddLayer(3, NEURON_FUNCTION_NONE, 0, 1); // input
	network->AddLayer(2, NEURON_FUNCTION_SIGMOID, WEIGHT_INIT_0); // output
	
	return (network);
}

ACarGenAIGameMode::ACarGenAIGameMode()
{
	srand (time(NULL));
	//DefaultPawnClass = ACarGenAIPawn::StaticClass();
	PlayerControllerClass = ACarGenAIPlayerController::StaticClass();
	HUDClass = ACarGenAIHud::StaticClass();
	//ConstructorHelpers::FObjectFinder<UBlueprint> CarClassFinder(TEXT("Blueprint'/Game/BP_CarGenAIBluePawn.BP_CarGenAIBluePawn'"));
	//if (CarClassFinder.Object)
		//CarClass = (UClass*)CarClassFinder.Object->GeneratedClass;
}

void	ACarGenAIGameMode::BeginPlay()
{
	Super::BeginPlay();
	TActorIterator<AActor> ActorItr = TActorIterator<AActor>(GetWorld());

	while (ActorItr)
	{
		if (ActorItr->GetName() == "SpawnPoint" && GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("SpawnPoint found")));
			spawnPoint = *ActorItr;
		}
		++ActorItr;
	}
	SetupInitialPopulation();
	SpawnPopulation();
}

void	ACarGenAIGameMode::SetupInitialPopulation()
{
	for (int n = 0; n < CarClass.Num(); ++n)
	{
		populations.Add(new vyn::neuralnetwork::Population(&CreateNeuralNetwork, populationSize));
		populations[n]->SetMutationChance(0.05);
		if (n < mutationRates.Num())
			populations[n]->SetMutationChance(mutationRates[n]);
	}
}

void	ACarGenAIGameMode::SpawnPopulation()
{
	for (int n = 0; n < populations.Num(); ++n)
	{
		if (populations[n] == nullptr)
			return ;

		if (GetWorld())
		{
			for (int i = 0; i < populations[n]->GetSize(); ++i)
			{
				FActorSpawnParameters SpawnParams;
				ACarGenAIPawn *carHandler = GetWorld()->SpawnActor<ACarGenAIPawn>(CarClass[n], spawnPoint->GetActorLocation(), spawnPoint->GetActorRotation(), SpawnParams);
				carHandler->SpawnDefaultController();
				carHandler->SetPerson(populations[n]->GetPersons()[i]);
				populations[n]->GetPersons()[i]->SetCustomData(carHandler);
				populations[n]->GetPersons()[i]->SetScore(0);
			}
			//if (GEngine)
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("New population spawned")));
		}
	}
}

void	ACarGenAIGameMode::RemovePopulation()
{
	for (int n = 0; n < populations.Num(); ++n)
	{
		if (populations[n] == nullptr)
		return ;

		if (GetWorld())
		{
			for (int i = 0; i < populations[n]->GetSize(); ++i)
			{
				ACarGenAIPawn *carHandler;

				carHandler = (ACarGenAIPawn *)populations[n]->GetPersons()[i]->GetCustomData();
				populations[n]->GetPersons()[i]->SetCustomData(nullptr);

				if (carHandler != nullptr)
				{
					carHandler->SetPerson(nullptr);
					carHandler->Destroy();
				}
			}
			//if (GEngine)
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Current population removed")));
		}
	}
}

bool	cmp(vyn::neuralnetwork::Person *a, vyn::neuralnetwork::Person *b)
{
	if (a->GetScore() > b->GetScore())
		return (true);
	return (false);
}

void	ACarGenAIGameMode::NewGeneration()
{
	for (int n = 0; n < populations.Num(); ++n)
	{
		int bestPopulationCount = FGenericPlatformMath::Sqrt(populationSize);
		if (GetWorld())
		{
			std::sort(populations[n]->GetPersons().begin(), populations[n]->GetPersons().end(), &cmp);
			for (int i = 0; i < bestPopulationCount; ++i)
			{
				populations[n]->GetPersons()[i]->Select();
			}
			populations[n]->CrossOver();
		}
	}
}