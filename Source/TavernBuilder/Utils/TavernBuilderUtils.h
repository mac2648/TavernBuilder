// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TavernBuilderUtils.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBUILDER_API UTavernBuilderUtils : public UObject
{
	GENERATED_BODY()

public:
	/*Returns the angle in deegres of the mouse from the center of the sceen
	* the start point is strait up from the center and goes clockwise.
	*/
	UFUNCTION(BlueprintCallable)
	static double GetMouseAngleFromScreenCenter();
	
};
