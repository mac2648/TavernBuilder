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
	Kitchen,
	Barrel,

	AllCategories
};

EObjectCategory operator++(EObjectCategory& Category, int);