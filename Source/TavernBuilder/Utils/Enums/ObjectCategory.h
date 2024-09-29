#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EObjectType
{
	Large,
	Medium,
	Small
};

UENUM(BlueprintType)
enum EObjectCategory //When adding a new value remember to add it to the functions GetObjectCategoriesByType and GetObjCategoryName on TavernBuilderUtils
{
	Chair,
	Table,
	// For kitchen props
	KitchenProps,
	// For kitchen furniture such as ovens and stoves
	KitchenBig,
	Barrel,
	Fireplace,
	// Storage includes cabinets, shelves, Chests, and fridges
	Storage,
	Bed,

	AllCategories
};

EObjectCategory operator++(EObjectCategory& Category, int);