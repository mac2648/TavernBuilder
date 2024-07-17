// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/PlayerComponents/DeleteToolComponent.h"
#include "TavernBuilder/Objects/PlaceableObjects.h"
#include "TavernBuilder/Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"

void UDeleteToolComponent::Execute(const FInputActionValue& Value)
{
	FVector Start = Cast<APlayerCharacter>(GetOwner())->GetFollowCamera()->GetComponentLocation();
	FVector LookingDirection = Cast<APlayerCharacter>(GetOwner())->GetControlRotation().Vector();

	FVector End = Start + LookingDirection * 1000000;

	FHitResult OutHit;
	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility);

	if (APlaceableObjects* Obj = Cast<APlaceableObjects>(OutHit.GetActor()))
	{
		Obj->Delete();
	}
}