#pragma once

#include "CoreMinimal.h"

class APlaceableObjects;
class UTexture2D;
enum EObjectType;

struct FObjOptionButtonInfo
{
	TSubclassOf<APlaceableObjects> Class;

	FString Name;

	int32 Cost;

	UTexture2D* Image;

	TEnumAsByte<EObjectType> Type;

public:
	void Clear();
	bool IsValid() const;
};