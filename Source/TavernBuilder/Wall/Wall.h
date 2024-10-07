// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

class AWallNode;

UCLASS()
class TAVERNBUILDER_API AWall : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWallNode> WallNodeClass;

	//defines the number of nodes in the wall
	UPROPERTY(EditAnywhere, Category = "Size")
	FVector2D WallSize;

	TArray<AWallNode*> Nodes;

	FVector2D PreviousSize = FVector2D(0, 0);
	
public:	
	// Sets default values for this actor's properties
	AWall();
	~AWall();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;
	void DeleteNodes();
	void CreateNodes();
	void AddNodes(int XStart, int YStart, const FVector& InitialLocation);
};
