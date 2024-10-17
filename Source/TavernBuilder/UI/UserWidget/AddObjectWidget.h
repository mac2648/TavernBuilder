// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPreviewButtonModule/UserWidget/ObjectPreviewWidget.h"
#include "TavernBuilder/Utils/Consts/ConstsUI.h"
#include "TavernBuilder/Utils/Enums/ObjectCategory.h"
#include "AddObjectWidget.generated.h"

class UObjectOptionOverlay;
class UAddObjectComponent;
class USlider;
class UChooseObjCategoryOverlay;

UCLASS()
class TAVERNBUILDER_API UAddObjectWidget : public UObjectPreviewWidget
{
	GENERATED_BODY()

	UAddObjectComponent* AddObjComp;

public:
	void SetAddObjComp(UAddObjectComponent* Comp) { AddObjComp = Comp; }
	void ShowAllObjs();
	void ApplyCatagory(UChooseObjCategoryOverlay* CategoryButton);

protected:
	virtual void NativeConstruct() override;

	virtual void ButtonClick(UObjectPreviewButton* PressedButton) override;

	virtual void ApplyTextButton(UTextButton* ClickedOverlay) override;
};
