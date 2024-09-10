// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Overlay.h"
#include "TavernBuilder/Utils/Enums/ObjectCategory.h"
#include "ChooseObjCategoryOverlay.generated.h"

class UButton;
class UTextBlock;
enum EObjectCategory;

/**
 * 
 */
UCLASS()
class TAVERNBUILDER_API UChooseObjCategoryOverlay : public UOverlay
{
	GENERATED_BODY()

	EObjectCategory Category;

	UButton* CategoryButton = nullptr;

	UTextBlock* CategoryText = nullptr;
	

public:
	void Initialize(EObjectCategory NewCategory);
};
