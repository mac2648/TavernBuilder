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
	
public:	
	APlaceableObjects();

	virtual void Tick(float DeltaTime) override;
	double GetMeshHeight() const { return Mesh->GetStaticMesh()->GetBounds().BoxExtent.Z; }

protected:
	virtual void BeginPlay() override;

};
