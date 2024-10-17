#pragma once

#include "CoreMinimal.h"

struct FObjectPreviewInfo
{
	FString Name;

	int32 Cost;

	UTexture2D* Image;

public:
	virtual void Clear()
	{
		Name = "";
		Cost = 0;
		Image = nullptr;
	}

	virtual bool IsValid() const
	{
		return Name != "" || Cost != 0 || Image != nullptr;
	}
};