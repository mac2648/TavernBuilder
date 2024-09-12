// Fill out your copyright notice in the Description page of Project Settings.

#include "TavernBuilder/PlayerComponents/AddObjectComponent.h"
#include "TavernBuilder/Objects/PlaceableObjects.h"
#include "TavernBuilder/Character/PlayerCharacter.h"
#include "TavernBuilder/PlayerComponents/PlaceToolComponent.h"
#include "TavernBuilder/UI/UserWidget/AddObjectWidget.h"
#include "TavernBuilder/UI/Overlay/ObjectOptionOverlay.h"
#include "TavernBuilder/Utils/Enums/ObjectCategory.h"

void UAddObjectComponent::BeginPlay()
{
	PlaceableObjectsList = NewObject<UObjectInfoArray>(this, PlaceableObjectsListClass);//<UObjectInfoArray>(PlaceableObjectsListClass)

	Super::BeginPlay();

	AddObjWidget = CreateWidget<UAddObjectWidget>(GetWorld(), AddWidgetClass);
	AddObjWidget->SetAddObjComp(this);
	AddObjWidget->AddToViewport();

	AddObjWidget->ShowAllObjs();

	AddObjWidget->SetVisibility(ESlateVisibility::Hidden);
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

void UAddObjectComponent::OnActivate(UActorComponent* Comp, bool IsReset)
{
	Super::OnActivate(Comp, IsReset);

	GetOwner()->GetInstigatorController<APlayerController>()->SetInputMode(FInputModeUIOnly());
	GetOwner()->GetInstigatorController<APlayerController>()->SetShowMouseCursor(true);

	AddObjWidget->SetVisibility(ESlateVisibility::Visible);
}

void UAddObjectComponent::OnDeactivate(UActorComponent* Comp)
{
	Super::OnDeactivate(Comp);

	GetOwner()->GetInstigatorController<APlayerController>()->SetInputMode(FInputModeGameOnly());
	GetOwner()->GetInstigatorController<APlayerController>()->SetShowMouseCursor(false);

	AddObjWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UAddObjectComponent::GetPlaceableObjectsListByCategory(EObjectCategory Category, TArray<FObjectInfo>& List) const
{
	List.Empty();

	if (Category == AllCategories)
	{
		List = GetPlaceableObjectsList();
		return;
	}

	for (int i = 0; i < PlaceableObjectsList->List.Num(); i++)
	{
		if (PlaceableObjectsList->List[i].Category == Category)
		{
			List.Add(PlaceableObjectsList->List[i]);
		}
	}
}