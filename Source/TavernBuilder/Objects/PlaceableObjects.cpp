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

void APlaceableObjects::Delete()
{
	if (ParentObj)
	{
		ParentObj->DetachObj(this);
	}

	TArray<APlaceableObjects*> ChildObjs;
	AttachedObjs.GetKeys(ChildObjs);

	for (APlaceableObjects* Obj : ChildObjs)
	{
		Obj->Delete();
	}

	Destroy();
}

void APlaceableObjects::Move(const FVector& NewWorldLocation)
{
	SetActorLocation(NewWorldLocation);

	TArray<APlaceableObjects*> ChildObjs;
	AttachedObjs.GetKeys(ChildObjs);

	for (APlaceableObjects* Obj : ChildObjs)
	{
		Obj->Move(NewWorldLocation + AttachedObjs[Obj]);
	}
}

void APlaceableObjects::AttachObj(APlaceableObjects* NewObj)
{
	FVector RelativePosition = NewObj->GetActorLocation() - GetActorLocation();

	AttachedObjs.Add(NewObj, RelativePosition);

	NewObj->SetParentObj(this);
}

void APlaceableObjects::DetachObj(APlaceableObjects* RemovedObj)
{
	AttachedObjs.Remove(RemovedObj);

	RemovedObj->RemoveParentObj();
}

void APlaceableObjects::SetParentObj(APlaceableObjects* Parent)
{
	ParentObj = Parent;
}

void APlaceableObjects::RemoveParentObj()
{
	ParentObj = nullptr;
}