// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/Utils/TavernBuilderUtils.h"
#include "Kismet/GameplayStatics.h"
#include "TavernBuilder/Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"

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