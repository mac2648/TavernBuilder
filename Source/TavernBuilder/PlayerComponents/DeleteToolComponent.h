// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TavernBuilder/PlayerComponents/ToolComponent.h"
#include "DeleteToolComponent.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBUILDER_API UDeleteToolComponent : public UToolComponent
{
	GENERATED_BODY()

protected:
	virtual void Execute(const FInputActionValue& Value) override;
	
};
