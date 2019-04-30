// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CarGenAIHud.h"
#include "CarGenAIPawn.h"
#include "WheeledVehicle.h"
#include "RenderResource.h"
#include "Shader.h"
#include "Engine/Canvas.h"
#include "WheeledVehicleMovementComponent.h"
#include "Engine/Font.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

#include "CarGenAIGameMode.h"

#define LOCTEXT_NAMESPACE "VehicleHUD"

#ifndef HMD_MODULE_INCLUDED
#define HMD_MODULE_INCLUDED 0
#endif

ACarGenAIHud::ACarGenAIHud()
{
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = Font.Object;
}

void ACarGenAIHud::DrawPopulationInfo(int x, int y, const FLinearColor &color, int n)
{
	const float HUDXRatio = Canvas->SizeX / 1280.f;
	const float HUDYRatio = Canvas->SizeY / 720.f;
	vyn::neuralnetwork::Population	*population = nullptr;
	ACarGenAIGameMode *gameMode = nullptr;

	if (GetWorld())
		gameMode = (ACarGenAIGameMode *)GetWorld()->GetAuthGameMode();

	if (!gameMode)
		return ;
	population = gameMode->GetPopulation(n);
	if (!population)
		return ;

	FVector2D ScaleVec(HUDYRatio * 0.8f, HUDYRatio * 0.8f);
	
	/*for (int i = 0; i < 10; ++i)
	{
		FCanvasTextItem LastBestScore(FVector2D(HUDXRatio * x, y - (i * 20)), FText::Format(LOCTEXT("ExampleFText", "{0} score {1}"),
			population->GetPersons()[9 - i]->GetId(),
			population->GetPersons()[9 - i]->GetScore()), HUDFont, color);
		LastBestScore.Scale = ScaleVec;
		Canvas->DrawItem(LastBestScore);
	}*/
	FCanvasTextItem TextItemMutationRate(FVector2D(HUDXRatio * x, y - (1 * 20)), FText::Format(LOCTEXT("ExampleFText", "Mutation rate: {0}%"),
		population->GetMutationChance() * 100), HUDFont, color);
	TextItemMutationRate.Scale = ScaleVec;
	Canvas->DrawItem(TextItemMutationRate);
	FCanvasTextItem TextItem(FVector2D(HUDXRatio * x, y - (2 * 20)), FText::Format(LOCTEXT("ExampleFText", "Generation: {0}"),
		population->GetCurrentGenerationId()), HUDFont, color);
	TextItem.Scale = ScaleVec;
	Canvas->DrawItem(TextItem);
}

void ACarGenAIHud::DrawHUD()
{
	Super::DrawHUD();

	DrawPopulationInfo(10, Canvas->SizeY - 20, FLinearColor::White, 0);
	//DrawPopulationInfo(10, Canvas->SizeY - 20, FLinearColor::Blue, 0);
	DrawPopulationInfo(160, Canvas->SizeY - 20, FLinearColor::Red, 1);
	DrawPopulationInfo(310, Canvas->SizeY - 20, FLinearColor::Green, 2);
	DrawPopulationInfo(460, Canvas->SizeY - 20, FLinearColor::Yellow, 3);
}

#undef LOCTEXT_NAMESPACE