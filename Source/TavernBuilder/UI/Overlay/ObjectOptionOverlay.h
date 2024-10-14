// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPreviewButtonModule/Button/ObjectPreviewButton.h"
#include "TavernBuilder/Utils/Structs/ObjOptionButtoninfo.h"
#include "ObjectOptionOverlay.generated.h"


class APlaceableObjects;
class UTextBlock;
class UButton;
class UImage;
enum EObjectType;

UCLASS()
class TAVERNBUILDER_API UObjectOptionOverlay : public UObjectPreviewButton
{
	GENERATED_BODY()

public:
	UObjectOptionOverlay();

	virtual void SetInfo(const FObjectPreviewInfo* NewInfo) override;

	inline TSubclassOf<APlaceableObjects> GetObjectClass() const { return static_cast<FObjOptionButtonInfo*>(Info)->Class; }
	inline EObjectType GetObjectType() const { return static_cast<FObjOptionButtonInfo*>(Info)->Type; }
};
