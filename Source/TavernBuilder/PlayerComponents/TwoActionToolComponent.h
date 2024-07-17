// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TavernBuilder/PlayerComponents/ToolComponent.h"
#include "TwoActionToolComponent.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBUILDER_API UTwoActionToolComponent : public UToolComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputAction* SecondaryInputAction;

	FInputBindingHandle* SecondaryActionBind;

protected:
	virtual void OnActivate(UActorComponent* Comp, bool IsReset) override;

	virtual void OnDeactivate(UActorComponent* Comp) override;

	virtual void SecondaryExecute(const FInputActionValue& Value);
};
