// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TavernBuilderUtils.generated.h"

enum EObjectCategory;
enum EObjectType;

/**
 * 
 */
UCLASS()
class TAVERNBUILDER_API UTavernBuilderUtils : public UObject
{
	GENERATED_BODY()

public:
	/*Returns the angle in deegres of the mouse from the center of the sceen
	* the start point is strait up from the center and goes clockwise.
	*/
	UFUNCTION(BlueprintCallable)
	static double GetMouseAngleFromScreenCenter();

	static void RaycastFromPlayerView(FHitResult& OutHit, FCollisionQueryParams& QueryParams, UObject* WorldContextObject);

	static FVector2D GetScreenCenter();

	static FString GetObjCategoryName(EObjectCategory Category);

	static void GetObjectCategoriesByType(EObjectType Type, TArray<EObjectCategory>& OutArray);
};
