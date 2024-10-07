// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/Wall/Wall.h"
#include "TavernBuilder/Wall/WallNode.h"
#include "EditorModeManager.h"
#include "RedirectingActorEditor/EditorMode/RedirectingActorMode.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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
	static bool First = true;

	if (First)
	{
		FEditorModeTools& ModeTools = GLevelEditorModeTools();
		ModeTools.ActivateMode(FRedirectingActorMode::EM_RedirectingActorMode);
		First = false;
	}

	Super::OnConstruction(Transform);

	if (WallSize != PreviousSize)
	{
		DeleteNodes();
		CreateNodes();
		PreviousSize = WallSize;
	}
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::DeleteNodes()
{
	TArray<AWallNode*> NodesToRemove;

	if (WallSize.X <= PreviousSize.X)
	{
		for (int i = PreviousSize.X - 1; i >= WallSize.X; i--)
		{
			for (int j = 0; j < WallSize.Y; j++)
			{
				NodesToRemove.Add(Nodes[PreviousSize.Y * i + j]);
			}
		}
	}

	if (WallSize.Y <= PreviousSize.Y)
	{
		for (int i = 0; i < WallSize.X; i++)
		{
			for (int j = PreviousSize.Y - 1; j >= WallSize.Y; j--)
			{
				NodesToRemove.Add(Nodes[PreviousSize.Y * i + j]);
			}
		}
	}

	for (AWallNode* Node : NodesToRemove)
	{
		Nodes.Remove(Node);
		Node->Destroy();
	}
}

void AWall::CreateNodes()
{
	FVector InitialLocation = GetActorLocation() + FVector(NodeSize/2, 0, NodeSize/2);
	if (WallNodeClass)
	{
		if (PreviousSize == FVector2D(0, 0))
		{
			AddNodes(0, 0, InitialLocation);
		}
		else
		{
			if (PreviousSize.X < WallSize.X)
			{
				AddNodes(PreviousSize.X, 0, InitialLocation);
			}

			if (PreviousSize.Y < WallSize.Y)
			{
				AddNodes(0, PreviousSize.Y, InitialLocation);
			}
		}
	}
}

void AWall::AddNodes(int XStart, int YStart, const FVector& InitialLocation)
{
	for (int i = XStart; i < WallSize.X; i++)
	{
		for (int j = YStart; j < WallSize.Y; j++)
		{
			FVector NodeLocation = InitialLocation + FVector(NodeSize * i, 0, NodeSize * j);
			FActorSpawnParameters SpawnParams;

			AWallNode* NewNode = GetWorld()->SpawnActor<AWallNode>(WallNodeClass, NodeLocation, FRotator::ZeroRotator, SpawnParams);

			if (NewNode)
			{
				Nodes.Add(NewNode);
				NewNode->SetFlags(RF_Transient);
				NewNode->SetObjOwner(this);
				NewNode->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}
}