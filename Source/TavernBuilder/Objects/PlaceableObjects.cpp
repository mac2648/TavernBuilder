// Fill out your copyright notice in the Description page of Project Settings.

#include "TavernBuilder/Objects/PlaceableObjects.h"

// Sets default values
APlaceableObjects::APlaceableObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void APlaceableObjects::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlaceableObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

