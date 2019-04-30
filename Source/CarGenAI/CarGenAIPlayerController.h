// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CarGenAIGameMode.h"
#include "CarGenAIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CARGENAI_API ACarGenAIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
	ACarGenAIPlayerController();

	virtual void	SetupInputComponent() override;
	
	void			NextPopulation();
};
