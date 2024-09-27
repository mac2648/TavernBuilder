#pragma once

#include "ObjOptionButtonInfo.h"
#include "ObjectInfo.generated.h"

class APlaceableObjects;
class UMaterialInstance;
class UTexture2D;
enum EObjectCategory;
enum EObjectType;

USTRUCT(BlueprintType)
struct FObjectInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlaceableObjects> Class;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> Materials;

	UPROPERTY(EditAnywhere)
	int32 Cost;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EObjectCategory> Category;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EObjectType> Type;

	UPROPERTY(EditAnywhere)
	UTexture2D* Image;

	FObjectInfo() {};
	//FObjectInfo(FObjectInfo& Other)
	//{
	//	Name = Other.Name;
	//	Class = Other.Class;
	//	Cost = Other.Cost;
	//	Category = Other.Category;
	//	Type = Other.Type;
	//	Image = Other.Image;

	//	for (int i = 0; i < Other.Materials.Num(); i++)
	//	{
	//		Materials.Add(Other.Materials[i]);
	//	}
	//}

	operator FObjOptionButtonInfo() const
	{
		FObjOptionButtonInfo OutInfo;

		OutInfo.Class = Class;
		OutInfo.Cost = Cost;
		OutInfo.Name = Name;
		OutInfo.Image = Image;
		OutInfo.Type = Type;
		return OutInfo;
	}
};

UCLASS(config = Game, BlueprintType, Blueprintable, MinimalAPI)
class UObjectInfoArray : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FObjectInfo> List;
};