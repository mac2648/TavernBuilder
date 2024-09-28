// Fill out your copyright notice in the Description page of Project Settings.

#include "TavernBuilder/Objects/PlaceableObjects.h"
#include "TavernBuilder/Utils/Enums/ObjectCategory.h"

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
		DetachObj(Obj);
	}

	Destroy();
}

void APlaceableObjects::Move(const FVector& NewWorldLocation)
{
	SetActorLocation(NewWorldLocation);
}

void APlaceableObjects::Rotate(const FRotator& AddedRotation)
{
	AddActorWorldRotation(AddedRotation);
}

void APlaceableObjects::AttachObj(APlaceableObjects* NewObj)
{
	FVector RelativePosition = NewObj->GetActorLocation() - GetActorLocation();

	AttachedObjs.Add(NewObj, RelativePosition);

	NewObj->SetParentObj(this);
	NewObj->GetMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform);
}

void APlaceableObjects::DetachObj(APlaceableObjects* RemovedObj)
{
	AttachedObjs.Remove(RemovedObj);

	RemovedObj->GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
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

void APlaceableObjects::GetAttachedObjs(TArray<APlaceableObjects*>& OutObjs) const
{
	TArray<APlaceableObjects*> ChildObjs;
	AttachedObjs.GetKeys(ChildObjs);

	for (APlaceableObjects* Obj : ChildObjs)
	{
		OutObjs.Add(Obj);
		Obj->GetAttachedObjs(OutObjs);
	}
	
}

void APlaceableObjects::EnableCollision()
{
	TArray<UStaticMeshComponent*> AllMeshes;

	GetComponents<UStaticMeshComponent>(AllMeshes);

	for (UStaticMeshComponent* Curr : AllMeshes)
	{
		Curr->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	TArray<APlaceableObjects*> AllAttachedObjs;
	GetAttachedObjs(AllAttachedObjs);

	for (APlaceableObjects* Obj : AllAttachedObjs)
	{
		Obj->EnableCollision();
	}
}

void APlaceableObjects::DisableCollision()
{
	TArray<UStaticMeshComponent*> AllMeshes;

	GetComponents<UStaticMeshComponent>(AllMeshes);

	for (UStaticMeshComponent* Curr : AllMeshes)
	{
		Curr->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	TArray<APlaceableObjects*> AllAttachedObjs;
	GetAttachedObjs(AllAttachedObjs);

	for (APlaceableObjects* Obj : AllAttachedObjs)
	{
		Obj->DisableCollision();
	}
}

void APlaceableObjects::SetTempHighLight(UMaterialInstance* HighLightMaterial)
{
	TArray<UStaticMeshComponent*> AllMeshes;

	GetComponents<UStaticMeshComponent>(AllMeshes);

	for (UStaticMeshComponent* Curr : AllMeshes)
	{
		Curr->SetOverlayMaterial(HighLightMaterial);
	}

	if (HighLightHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(HighLightHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(HighLightHandle, this, &APlaceableObjects::RemoveHighlight, 0.004);
}

void APlaceableObjects::SetHighLight(UMaterialInstance* HighLightMaterial)
{
	TArray<UStaticMeshComponent*> AllMeshes;

	GetComponents<UStaticMeshComponent>(AllMeshes);

	for (UStaticMeshComponent* Curr : AllMeshes)
	{
		Curr->SetOverlayMaterial(HighLightMaterial);
	}

	if (HighLightHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(HighLightHandle);
	}
}

void APlaceableObjects::RemoveHighlight()
{
	TArray<UStaticMeshComponent*> AllMeshes;

	GetComponents<UStaticMeshComponent>(AllMeshes);

	for (UStaticMeshComponent* Curr : AllMeshes)
	{
		Curr->SetOverlayMaterial(nullptr);
	}

}

bool APlaceableObjects::CanAttach(const APlaceableObjects* Other) const
{
	if (Type == Large && (Other->Type == Small || Other->Type == Medium) )
	{
		return true;
	}
	else if (Type == Medium && (Other->Type == Small || Other->Type == Medium) )
	{
		return true;
	}

	return false;
}