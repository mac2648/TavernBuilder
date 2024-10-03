// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallNode.generated.h"

const float NodeSize = 20;

UCLASS()
class TAVERNBUILDER_API AWallNode : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	
public:	
	// Sets default values for this actor's properties
	AWallNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
