#pragma once

#include "CoreMinimal.h"

class APlaceableObjects;
class UTexture2D;

struct FObjOptionButtonInfo
{
	TSubclassOf<APlaceableObjects> Class;

	FText Name;

	int32 Cost;

	UTexture2D* Image;

public:
	void Clear();
	bool IsValid() const;
};