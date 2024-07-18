// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/PlayerComponents/PlaceToolComponent.h"
#include "TavernBuilder/Objects/PlaceableObjects.h"
#include "InputActionValue.h"
#include "TavernBuilder/Utils/TavernBuilderUtils.h"

void UPlaceToolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (MovingObj)
	{
		FHitResult OutHit;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MovingObj);

		TArray<APlaceableObjects*> AttachedObjs;
		MovingObj->GetAttachedObjs(AttachedObjs);

		for (APlaceableObjects* Obj : AttachedObjs)
		{
			QueryParams.AddIgnoredActor(Obj);
		}

		UTavernBuilderUtils::RaycastFromPlayerView(OutHit, QueryParams, this);

		FVector MoveLocation = OutHit.Location;

		MovingObj->Move(MoveLocation);
	}
}

void UPlaceToolComponent::SetMovingObj(APlaceableObjects* ObjToMove)
{
	MovingObj = ObjToMove; 
	if (MovingObj)
	{
		MovingObj->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void UPlaceToolComponent::Execute(const FInputActionValue& Value)
{
	if (MovingObj)
	{
		FHitResult OutHit;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MovingObj);

		TArray<APlaceableObjects*> AttachedObjs;
		MovingObj->GetAttachedObjs(AttachedObjs);

		for (APlaceableObjects* Obj : AttachedObjs)
		{
			QueryParams.AddIgnoredActor(Obj);
		}

		UTavernBuilderUtils::RaycastFromPlayerView(OutHit, QueryParams, this);

		if (APlaceableObjects* Obj = Cast<APlaceableObjects>(OutHit.GetActor()))
		{
			Obj->AttachObj(MovingObj);
		}

		MovingObj->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MovingObj = nullptr;
	}
	else
	{
		FHitResult OutHit;
		FCollisionQueryParams QueryParams;

		UTavernBuilderUtils::RaycastFromPlayerView(OutHit, QueryParams, this);

		if (APlaceableObjects* Obj = Cast<APlaceableObjects>(OutHit.GetActor()))
		{
			SetMovingObj(Obj);

			if (APlaceableObjects* ParentObj = Obj->GetParentObj())
			{
				ParentObj->DetachObj(Obj);
			}
		}
	}
}

void UPlaceToolComponent::SecondaryExecute(const FInputActionValue& Value)
{
	float RotationValue = Value.Get<float>();

	if (MovingObj)
	{
		MovingObj->AddActorWorldRotation(FRotator(0, RotationValue * 10, 0));
	}
}