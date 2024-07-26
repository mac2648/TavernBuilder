// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tavernbuilder/PlayerComponents/ToolComponent.h"
#include "AddObjectComponent.generated.h"

/**
 * 
 */
class APlaceableObjects;
class UAddObjectWidget;
struct FObjOptionButtonInfo;
struct FImage;

UENUM(BlueprintType)
enum EObjectCategory
{
	Chair,
	Table
};

USTRUCT(BlueprintType)
struct FObjectInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlaceableObjects> Class;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> Materials;

	UPROPERTY(EditAnywhere)
	int32 Cost;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EObjectCategory> Category;

	UPROPERTY(EditAnywhere)
	UTexture2D* Image;

	operator FObjOptionButtonInfo() const;
};

UCLASS()
class TAVERNBUILDER_API UAddObjectComponent : public UToolComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APlaceableObjects> ObjectToSpawn;

	UPROPERTY(EditDefaultsOnly)
	TArray<FObjectInfo> PlaceableObjectsList;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAddObjectWidget> AddWidgetClass;

	UAddObjectWidget* AddObjWidget;

public:
	const TArray<FObjectInfo>& GetPlaceableObjectsList() const {return PlaceableObjectsList; }

protected:
	virtual void BeginPlay() override;
	
	virtual void Execute(const FInputActionValue& Value) override;
};
