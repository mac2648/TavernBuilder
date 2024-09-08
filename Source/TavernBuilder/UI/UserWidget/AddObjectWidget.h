// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TavernBuilder/Utils/Consts.h"
#include "AddObjectWidget.generated.h"

class UObjectOptionOverlay;
class UAddObjectComponent;
class USlider;

using namespace UIConsts;

UCLASS()
class TAVERNBUILDER_API UAddObjectWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UObjectOptionOverlay* NewObjsButtons[NumNewObjBnt];

	UAddObjectComponent* AddObjComp;

	USlider* Slider;

public:
	void SetAddObjComp(UAddObjectComponent* Comp) { AddObjComp = Comp; }
	void ShowAllObjs();

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void MoveButtons(float Percent);

	UFUNCTION()
	void ButtonClick(UObjectOptionOverlay* PressedButton);
};
