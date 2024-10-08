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
enum EObjectCategory;
enum EObjectType;

UCLASS()
class TAVERNBUILDER_API UAddObjectComponent : public UToolComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UObjectInfoArray> PlaceableObjectsListClass;

	UObjectInfoArray* PlaceableObjectsList;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAddObjectWidget> AddWidgetClass;

	TSubclassOf<APlaceableObjects> ObjectToSpawn;
	EObjectType SpawnObjectType;

	UAddObjectWidget* AddObjWidget;

	FObjectInfo* AllPlaceableObjList;
	int NumAllPlaceableObjList;

public:
	const TArray<FObjectInfo>& GetPlaceableObjectsList() const {return PlaceableObjectsList->List; }

	void GetPlaceableObjectsListByCategory(EObjectCategory Category, TArray<FObjectInfo>& OutList) const;

	void SetObjectClass(TSubclassOf<APlaceableObjects> NewClass) { ObjectToSpawn = NewClass; }
	void SetObjectType(EObjectType NewType) { SpawnObjectType = NewType; }

protected:
	virtual void BeginPlay() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
	
	virtual void Execute(const FInputActionValue& Value) override;

	virtual void OnActivate(UActorComponent* Comp, bool IsReset) override;
	virtual void OnDeactivate(UActorComponent* Comp) override;

	friend UAddObjectWidget;
};
