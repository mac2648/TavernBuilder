// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TavernBuilder/PlayerComponents/TwoActionToolComponent.h"
#include "PlaceToolComponent.generated.h"

/**
 * 
 */

class APlaceableObjects;

UCLASS()
class TAVERNBUILDER_API UPlaceToolComponent : public UTwoActionToolComponent
{
	GENERATED_BODY()
	
protected:
	APlaceableObjects* MovingObj = nullptr;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMovingObj(APlaceableObjects* ObjToMove);

protected:
	virtual void Execute(const FInputActionValue& Value) override;
	virtual void SecondaryExecute(const FInputActionValue& Value) override;
};
