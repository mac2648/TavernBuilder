// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tavernbuilder/PlayerComponents/ToolComponent.h"
#include "AddObjectComponent.generated.h"

/**
 * 
 */
class APlaceableObjects;

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
	FName Name;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlaceableObjects> Class;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> Materials;

	UPROPERTY(EditAnywhere)
	int32 Cost;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EObjectCategory> Category;
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

protected:
	virtual void BeginPlay() override;
	
	virtual void Execute(const FInputActionValue& Value) override;
};
