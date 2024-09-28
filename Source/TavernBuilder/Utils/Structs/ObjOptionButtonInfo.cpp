#pragma once

#include "TavernBuilder/Utils/Structs/ObjOptionButtonInfo.h"
#include "TavernBuilder/Objects/PlaceableObjects.h"
#include "TavernBuilder/Utils/Enums/ObjectCategory.h"

void FObjOptionButtonInfo::Clear()
{
	Class = nullptr;
	Name = "";
	Cost = 0;
	Image = nullptr;
	Type = EObjectType::Small;
}

bool FObjOptionButtonInfo::IsValid() const
{
	return Class != nullptr || Name != "" || Cost != 0 || Image != nullptr;
}
