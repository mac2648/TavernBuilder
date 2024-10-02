#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EObjectType
{
	//cannot be stacked
	Large,
	//can be placed on large and medium (can stack medium on medium)
	Medium,
	//can be placed onlarge and medium (cannot stack small on small)
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
	Light,

	AllCategories
};

EObjectCategory operator++(EObjectCategory& Category, int);