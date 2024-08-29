// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaceableObjects.generated.h"

UCLASS()
class TAVERNBUILDER_API APlaceableObjects : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	TMap<APlaceableObjects*, FVector> AttachedObjs;

	APlaceableObjects* ParentObj = nullptr;

private:
	FTimerHandle HighLightHandle;
	
public:	
	APlaceableObjects();

	virtual void Tick(float DeltaTime) override;
	double GetMeshHeight() const { return Mesh->GetStaticMesh()->GetBounds().BoxExtent.Z; }
	UStaticMeshComponent* GetMesh() const { return Mesh; }

	void Delete();
	void Move(const FVector& NewWorldLocation);

	void AttachObj(APlaceableObjects* NewObj);
	void DetachObj(APlaceableObjects* RemovedObj);

	APlaceableObjects* GetParentObj() const { return ParentObj; }

	void GetAttachedObjs(TArray<APlaceableObjects*>& OutObjs) const;

	void SetTempHighLight(UMaterialInstance* HighLightMaterial);
	void SetHighLight(UMaterialInstance* HighLightMaterial);
	void RemoveHighlight() { Mesh->SetOverlayMaterial(nullptr); }


protected:
	virtual void BeginPlay() override;

	void SetParentObj(APlaceableObjects* Parent);
	void RemoveParentObj();
};
