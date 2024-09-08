#pragma once

#include "TavernBuilder/Utils/Enums/ObjectCategory.h"
#include "ObjOptionButtonInfo.h"
#include "ObjectInfo.generated.h"

class APlaceableObjects;
class UMaterialInstance;
class UTexture2D;

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

	operator FObjOptionButtonInfo() const
	{
		FObjOptionButtonInfo OutInfo;
		OutInfo.Class = Class;
		OutInfo.Cost = Cost;
		OutInfo.Name = Name;
		OutInfo.Image = Image;
		return OutInfo;
	}
};