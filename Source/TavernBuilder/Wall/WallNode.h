// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RedirectingActorModule/Interface/RedirectingActorInterface.h"
#include "WallNode.generated.h"

const float NodeSize = 20;

class AWall;

UCLASS()
class TAVERNBUILDER_API AWallNode : public AActor, public IRedirectingActorInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	
	UMaterialInstanceDynamic* Material;

public:	
	
	AWallNode();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetMaterial(UMaterialInstance* NewMat, int X, int Y);

	friend AWall;
};
