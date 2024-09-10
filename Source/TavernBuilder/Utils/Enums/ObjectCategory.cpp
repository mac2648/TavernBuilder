#pragma once

#include "TavernBuilder/Utils/Enums/ObjectCategory.h"

EObjectCategory operator++(EObjectCategory& Category, int)
{
	Category = static_cast<EObjectCategory>(static_cast<uint8>(Category) + 1);
	return Category;
}