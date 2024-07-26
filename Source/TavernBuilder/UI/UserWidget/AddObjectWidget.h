// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AddObjectWidget.generated.h"

class UObjectOptionOverlay;
class UAddObjectComponent;

const int NUMBER_OF_BUTTONS = 50;

UCLASS()
class TAVERNBUILDER_API UAddObjectWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UObjectOptionOverlay* NewObjsButtons[NUMBER_OF_BUTTONS];

	UAddObjectComponent* AddObjComp;

public:
	void SetAddObjComp(UAddObjectComponent* Comp) { AddObjComp = Comp; }
	void ShowAllObjs();

protected:
	virtual void NativeConstruct() override;
};
