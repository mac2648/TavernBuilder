// Fill out your copyright notice in the Description page of Project Settings.

#include "TavernBuilder/PlayerComponents/AddObjectComponent.h"
#include "TavernBuilder/Objects/PlaceableObjects.h"
#include "TavernBuilder/Character/PlayerCharacter.h"

void UAddObjectComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAddObjectComponent::Execute(const FInputActionValue& Value)
{
	FVector FowardVector = Cast<APlayerCharacter>(GetOwner())->GetControlRotation().Vector();
	FowardVector.Z = 0;
	FVector SpawnLocation = GetOwner()->GetActorLocation() + FowardVector * 50;
	SpawnLocation.Z += 50;

	FRotator Rotation = FRotator::ZeroRotator;

	GetWorld()->SpawnActor<APlaceableObjects>(ObjectToSpawn, SpawnLocation, Rotation);
}