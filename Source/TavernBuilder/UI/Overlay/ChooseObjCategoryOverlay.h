// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPreviewButtonModule/Button/TextButton.h"
#include "TavernBuilder/Utils/Enums/ObjectCategory.h"
#include "ChooseObjCategoryOverlay.generated.h"

class UButton;
class UTextBlock;
enum EObjectCategory;

UCLASS()
class TAVERNBUILDER_API UChooseObjCategoryOverlay : public UTextButton
{
	GENERATED_BODY()

private:
	EObjectCategory Category;

public:
	EObjectCategory GetCategory() const { return Category; }
	void SetCategory(EObjectCategory NewCategory) { Category = NewCategory; }
};
