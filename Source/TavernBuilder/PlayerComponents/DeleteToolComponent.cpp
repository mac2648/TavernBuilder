// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/PlayerComponents/DeleteToolComponent.h"
#include "TavernBuilder/Objects/PlaceableObjects.h"
#include "TavernBuilder/Utils/TavernBuilderUtils.h"

void UDeleteToolComponent::Execute(const FInputActionValue& Value)
{
	FHitResult OutHit;
	FCollisionQueryParams QueryParams;

	UTavernBuilderUtils::RaycastFromPlayerView(OutHit, QueryParams, this);

	if (APlaceableObjects* Obj = Cast<APlaceableObjects>(OutHit.GetActor()))
	{
		Obj->Delete();
	}
}