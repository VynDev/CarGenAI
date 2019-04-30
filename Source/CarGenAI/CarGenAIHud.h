// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "CarGenAIHud.generated.h"


UCLASS(config = Game)
class ACarGenAIHud : public AHUD
{
	GENERATED_BODY()

public:
	ACarGenAIHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
	void		DrawPopulationInfo(int x, int y, const FLinearColor &color, int n);
};
