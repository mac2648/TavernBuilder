// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Overlay.h"
#include "ObjectOptionOverlay.generated.h"


class APlaceableObjects;
class UTextBlock;
class UButton;

struct FObjOptionButtonInfo
{
	TSubclassOf<APlaceableObjects> Class;

	FText Name;

	int32 Cost;

	FImage* Image;
};


UCLASS()
class TAVERNBUILDER_API UObjectOptionOverlay : public UOverlay
{
	GENERATED_BODY()

protected:

	FObjOptionButtonInfo Info;
	
	UTextBlock* Text;

	UButton* Button;

public:
	void SetInfo(FObjOptionButtonInfo& NewInfo);
	void CreateUI();
};
