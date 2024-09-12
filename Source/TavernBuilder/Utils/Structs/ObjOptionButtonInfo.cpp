#pragma once

#include "TavernBuilder/Utils/Structs/ObjOptionButtonInfo.h"
#include "TavernBuilder/Objects/PlaceableObjects.h"

void FObjOptionButtonInfo::Clear()
{
	Class = nullptr;
	Name = FText::FromString("");
	Cost = 0;
	Image = nullptr;
}

bool FObjOptionButtonInfo::IsValid() const
{
	return Class != nullptr || !Name.EqualTo(FText::FromString("")) || Cost != 0 || Image != nullptr;
}
