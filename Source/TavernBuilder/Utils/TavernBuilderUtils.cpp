// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/Utils/TavernBuilderUtils.h"
#include "Kismet/GameplayStatics.h"
#include "TavernBuilder/Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "TavernBuilder/Utils/Enums/ObjectCategory.h"

double UTavernBuilderUtils::GetMouseAngleFromScreenCenter()
{
	// Getting viewport size
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	// Getting mouse position
	FVector2D Mouse;
	UGameViewportClient* ViewportClient = GEngine->GameViewport;
	ViewportClient->GetMousePosition(Mouse);

	Mouse -= ViewportSize / 2;

	double Hipotenuse = FMath::Sqrt(FMath::Pow(Mouse.X, 2) + FMath::Pow(Mouse.Y, 2));
	double Sin = (Mouse.Y / Hipotenuse);

	double Angle = FMath::Abs(FMath::Asin(Sin) * 2 / UE_PI) * 90;

	if (Mouse.X >= 0 && Mouse.Y <= 0)
	{
		Angle = 90 - Angle;
	}
	else if (Mouse.X > 0 && Mouse.Y > 0)
	{
		Angle += 90;
	}
	else if (Mouse.X <= 0 && Mouse.Y >= 0)
	{
		Angle = 270 - Angle;
	}
	else if (Mouse.X < 0 && Mouse.Y < 0)
	{
		Angle += 270;
	}

	return Angle;
}

void UTavernBuilderUtils::RaycastFromPlayerView(FHitResult& OutHit, FCollisionQueryParams& QueryParams, UObject* WorldContextObject)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(WorldContextObject, 0));

	FVector Start = Player->GetFollowCamera()->GetComponentLocation();
	FVector LookingDirection = Player->GetControlRotation().Vector();

	FVector End = Start + LookingDirection * 1000000;

	WorldContextObject->GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, QueryParams);
}

FVector2D UTavernBuilderUtils::GetScreenCenter()
{
	FVector2D ScreenCenter;
	GEngine->GameViewport->GetViewportSize(ScreenCenter);

	ScreenCenter /= 2;
	return ScreenCenter;
}

FString UTavernBuilderUtils::GetObjCategoryName(EObjectCategory Category)
{
	switch (Category)
	{
	case Chair:
		return "Chairs";
		break;
	case Table:
		return "Tables";
		break;
	case Kitchen:
		return "Kitchen";
		break;
	case Barrel:
		return "Barrel";
		break;
	case AllCategories:
		return "All";
		break;
	default:
		return "Invalid";
		break;
	}
}

void UTavernBuilderUtils::GetObjectCategoriesByType(EObjectType Type, TArray<EObjectCategory>& OutArray)
{
	OutArray.Empty();

	switch (Type)
	{
	case Large:
		OutArray.Add(Chair);
		OutArray.Add(Table);
		OutArray.Add(Barrel);
		break;
	case Small:
		OutArray.Add(Kitchen);
		break;
	}
}