#pragma once

#include "ObjectPreviewButtonModule/Struct/ObjectPreviewInfo.h"

class APlaceableObjects;
enum EObjectType;

struct FObjOptionButtonInfo : public FObjectPreviewInfo
{
	TSubclassOf<APlaceableObjects> Class;

	TEnumAsByte<EObjectType> Type;

public:
	virtual void Clear() override;
	virtual bool IsValid() const override;
};