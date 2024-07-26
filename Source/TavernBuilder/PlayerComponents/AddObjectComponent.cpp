// Fill out your copyright notice in the Description page of Project Settings.

#include "TavernBuilder/PlayerComponents/AddObjectComponent.h"
#include "TavernBuilder/Objects/PlaceableObjects.h"
#include "TavernBuilder/Character/PlayerCharacter.h"
#include "TavernBuilder/PlayerComponents/PlaceToolComponent.h"
#include "TavernBuilder/UI/UserWidget/AddObjectWidget.h"
#include "TavernBuilder/UI/Overlay/ObjectOptionOverlay.h"

void UAddObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	AddObjWidget = CreateWidget<UAddObjectWidget>(GetWorld(), AddWidgetClass);
	AddObjWidget->SetAddObjComp(this);
	AddObjWidget->AddToViewport();

	AddObjWidget->ShowAllObjs();
}

void UAddObjectComponent::Execute(const FInputActionValue& Value)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner());

	FVector FowardVector = Player->GetControlRotation().Vector();
	FowardVector.Z = 0;
	FVector SpawnLocation = GetOwner()->GetActorLocation() + FowardVector * 50;
	SpawnLocation.Z += 50;

	FRotator Rotation = FRotator::ZeroRotator;

	APlaceableObjects* SpawnedObj = GetWorld()->SpawnActor<APlaceableObjects>(ObjectToSpawn, SpawnLocation, Rotation);
	UPlaceToolComponent* PlaceTool = Player->GetPlaceToolComp();

	Player->ActivateTool(ETools::MOVE);

	PlaceTool->SetMovingObj(SpawnedObj);
}

FObjectInfo::operator FObjOptionButtonInfo() const
{
	FObjOptionButtonInfo OutInfo;
	OutInfo.Class = Class;
	OutInfo.Cost = Cost;
	OutInfo.Name = Name;
	OutInfo.Image = Image;
	return OutInfo;
}