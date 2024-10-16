// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaceableObjects.generated.h"

enum EObjectType;
class UAddObjectComponent;

UCLASS()
class TAVERNBUILDER_API APlaceableObjects : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	TMap<APlaceableObjects*, FVector> AttachedObjs;

	APlaceableObjects* ParentObj = nullptr;

	EObjectType Type;

private:
	FTimerHandle HighLightHandle;
	bool Falling = false;
	
public:	
	APlaceableObjects();

	virtual void Tick(float DeltaTime) override;
	double GetMeshHeight() const { return Mesh->GetStaticMesh()->GetBounds().BoxExtent.Z; }
	UStaticMeshComponent* GetMesh() const { return Mesh; }

	void Delete();
	void Move(const FVector& NewWorldLocation);
	void Rotate(const FRotator& AddedRotation);
	void Fall(float DeltaTime);

	void AttachObj(APlaceableObjects* NewObj);
	void DetachObj(APlaceableObjects* RemovedObj);

	APlaceableObjects* GetParentObj() const { return ParentObj; }

	void GetAttachedObjs(TArray<APlaceableObjects*>& OutObjs) const;

	void SetTempHighLight(UMaterialInstance* HighLightMaterial);
	void SetHighLight(UMaterialInstance* HighLightMaterial);
	void RemoveHighlight();

	void EnableCollision();
	void DisableCollision();

	EObjectType GetObjectType() const { return Type; }
	bool CanAttach(const APlaceableObjects* Other) const;

protected:
	virtual void BeginPlay() override;

	void SetParentObj(APlaceableObjects* Parent);
	void RemoveParentObj();

	friend UAddObjectComponent;
};
