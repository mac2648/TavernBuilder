// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tavernbuilder/PlayerComponents/ToolComponent.h"
#include "AddObjectComponent.generated.h"

/**
 * 
 */

class APlaceableObjects;
UCLASS()
class TAVERNBUILDER_API UAddObjectComponent : public UToolComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APlaceableObjects> ObjectToSpawn;

protected:
	virtual void BeginPlay() override;
	
	virtual void Execute(const FInputActionValue& Value) override;
};
