// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "CarGenAIPawn.h"
#include "NeuralNetwork.h"
#include "CarGenAIGameMode.generated.h"

UCLASS(minimalapi)
class ACarGenAIGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACarGenAIGameMode();

	virtual void 								BeginPlay() override;

	void										SetupInitialPopulation();
	void										SpawnPopulation();
	void										RemovePopulation();
	void										NewGeneration();
	vyn::neuralnetwork::Population				*GetPopulation(int n) {return (n < populations.Num() ? populations[n] : nullptr);};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Population)
	TArray<TSubclassOf<class ACarGenAIPawn>>	CarClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Population)
	TArray<float>								mutationRates;
	AActor										*spawnPoint = nullptr;

	TArray<vyn::neuralnetwork::Population *>	populations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Population)
	int											populationSize = 25;

	TArray<TArray<ACarGenAIPawn *>> carPools;
};