// Fill out your copyright notice in the Description page of Project Settings.

#include "TavernBuilder/PlayerComponents/PaintToolComponent.h"
#include "TavernBuilder/Utils/Structs/PaintInfo.h"
#include "InputActionValue.h"
#include "TavernBuilder/Utils/TavernBuilderUtils.h"
#include "TavernBuilder/Wall/Wall.h"
#include "TavernBuilder/Wall/WallNode.h"

void UPaintToolComponent::BeginPlay()
{
	Super::BeginPlay();

	PaintList = NewObject<UPaintInfoList>(this, PaintListClass);

	AllPaintsSize = PaintList->List.Num();

	AllPaints = new FPaintInfo[AllPaintsSize];
	
	for (int i = 0; i < AllPaintsSize; i++)
	{
		AllPaints[i] = PaintList->List[i];
	}

	PaintList->List.Empty();
}

void UPaintToolComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	delete[] AllPaints;
}

void UPaintToolComponent::Execute(const FInputActionValue& Value)
{
	bool bValue = Value.Get<bool>();

	if (bValue)
	{
		FHitResult Hit;
		FCollisionQueryParams Params;

		UTavernBuilderUtils::RaycastFromPlayerView(Hit, Params, this);

		if (AWallNode* HitWall = Cast<AWallNode>(Hit.GetActor()))
		{
			Cast<AWall>(HitWall->GetAttachParentActor())->SetMaterial(PaintMaterial);
		}
	}
}