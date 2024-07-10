// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/PlayerComponents/PlaceToolComponent.h"
#include "TavernBuilder/Character/PlayerCharacter.h"
#include "TavernBuilder/Objects/PlaceableObjects.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"

void UPlaceToolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (MovingObj)
	{
		FVector Start = Cast<APlayerCharacter>(GetOwner())->GetFollowCamera()->GetComponentLocation();
		FVector LookingDirection = Cast<APlayerCharacter>(GetOwner())->GetControlRotation().Vector();

		FVector End = Start + LookingDirection * 1000000;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MovingObj);

		FHitResult OutHit;
		GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility , QueryParams);

		FVector MoveLocation = OutHit.Location;
		
		//MoveLocation.Z += MovingObj->GetMeshHeight();

		MovingObj->SetActorLocation(MoveLocation);
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
		MovingObj->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MovingObj = nullptr;
	}
	else
	{
		FVector Start = Cast<APlayerCharacter>(GetOwner())->GetFollowCamera()->GetComponentLocation();
		FVector LookingDirection = Cast<APlayerCharacter>(GetOwner())->GetControlRotation().Vector();

		FVector End = Start + LookingDirection * 1000000;

		FHitResult OutHit;
		GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility);

		if (APlaceableObjects* Obj = Cast<APlaceableObjects>(OutHit.GetActor()))
		{
			SetMovingObj(Obj);
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