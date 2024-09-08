// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tavernbuilder/PlayerComponents/ToolComponent.h"
#include "TavernBuilder/Utils/Structs/ObjectInfo.h"
#include "AddObjectComponent.generated.h"

/**
 * 
 */
class APlaceableObjects;
class UAddObjectWidget;
struct FObjOptionButtonInfo;
struct FImage;

UCLASS()
class TAVERNBUILDER_API UAddObjectComponent : public UToolComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FObjectInfo> PlaceableObjectsList;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAddObjectWidget> AddWidgetClass;

	TSubclassOf<APlaceableObjects> ObjectToSpawn;
	UAddObjectWidget* AddObjWidget;

public:
	const TArray<FObjectInfo>& GetPlaceableObjectsList() const {return PlaceableObjectsList; }
	void SetObjectClass(TSubclassOf<APlaceableObjects> NewClass) { ObjectToSpawn = NewClass; }

protected:
	virtual void BeginPlay() override;
	
	virtual void Execute(const FInputActionValue& Value) override;

	virtual void OnActivate(UActorComponent* Comp, bool IsReset) override;
	virtual void OnDeactivate(UActorComponent* Comp) override;

	friend UAddObjectWidget;
};
