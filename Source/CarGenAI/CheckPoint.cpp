// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoint.h"
#include "CarGenAIPawn.h"

ACheckPoint::ACheckPoint()
{
	OnActorBeginOverlap.AddDynamic(this, &ACheckPoint::AddScore);
}

void	ACheckPoint::AddScore(AActor *OverlappedActor, AActor *otherActor)
{
	ACarGenAIPawn *car;

	car = dynamic_cast<ACarGenAIPawn *>(otherActor);
	if (car == nullptr)
		return ;
	car->AddScore(this, scoreToAdd);
}

