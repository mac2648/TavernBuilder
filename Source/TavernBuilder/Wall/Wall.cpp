// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/Wall/Wall.h"
#include "TavernBuilder/Wall/WallNode.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AWall::~AWall()
{
	DeleteNodes();
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWall::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	DeleteNodes();
	CreateNodes();
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::DeleteNodes()
{
	for (AWallNode* Node : Nodes)
	{
		Node->Destroy();
	}

	Nodes.Empty();
}

void AWall::CreateNodes()
{
	if (!Nodes.IsEmpty())
	{
		DeleteNodes();
	}

	FVector InitialLocation = GetActorLocation() + FVector(NodeSize/2, 0, NodeSize/2);
	if (WallNodeClass)
	{
		for (int i = 0; i < WallSize.X; i++)
		{
			for (int j = 0; j < WallSize.Y; j++)
			{
				FVector NodeLocation = InitialLocation + FVector(NodeSize * i, 0, NodeSize * j);
				FActorSpawnParameters SpawnParams;

				AWallNode* NewNode = GetWorld()->SpawnActor<AWallNode>(WallNodeClass, NodeLocation, FRotator::ZeroRotator, SpawnParams);

				if (NewNode)
				{
					Nodes.Add(NewNode);
					NewNode->SetFlags(RF_Transient);
				}

			}
		}
	}
}