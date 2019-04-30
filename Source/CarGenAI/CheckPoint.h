// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CheckPoint.generated.h"

/**
 * 
 */
UCLASS()
class CARGENAI_API ACheckPoint : public ATriggerBox
{
	GENERATED_BODY()

	ACheckPoint();
	
	UFUNCTION()
	virtual void	AddScore(AActor *OverlappedActor, AActor *otherActor);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VNN")
	int	scoreToAdd = 1;
};
