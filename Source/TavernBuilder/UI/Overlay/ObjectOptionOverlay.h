// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Overlay.h"
#include "TavernBuilder/Utils/Structs/ObjOptionButtoninfo.h"
#include "ObjectOptionOverlay.generated.h"


class APlaceableObjects;
class UTextBlock;
class UButton;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventOptionButtonClick, UObjectOptionOverlay*, ClickedOverlay);

UCLASS()
class TAVERNBUILDER_API UObjectOptionOverlay : public UOverlay
{
	GENERATED_BODY()

protected:

	FObjOptionButtonInfo Info;
	
	UTextBlock* Text;

	UButton* Button;

	UImage* Image;

public:
	void SetInfo(const FObjOptionButtonInfo& NewInfo);
	void ClearInfo();

	void CreateUI();

	TSubclassOf<APlaceableObjects> GetObjectClass() const { return Info.Class; }
	bool IsValid() const { return Info.IsValid(); }

	FEventOptionButtonClick OnOptionButtonClick;

protected:
	UFUNCTION()
	void OptionButtonClick();
};
