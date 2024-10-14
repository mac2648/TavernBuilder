// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TavernBuilder/PlayerComponents/ToolComponent.h"
#include "PaintToolComponent.generated.h"

class UPaintInfoList;
struct FPaintInfo;
/**
 * 
 */
UCLASS()
class TAVERNBUILDER_API UPaintToolComponent : public UToolComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaintInfoList> PaintListClass;
	UPaintInfoList* PaintList;
	FPaintInfo* AllPaints;

	int AllPaintsSize = 0;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* PaintMaterial;

protected:
	virtual void BeginPlay() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual void Execute(const FInputActionValue& Value) override;

	//virtual void OnActivate(UActorComponent* Comp, bool IsReset) override;
	//virtual void OnDeactivate(UActorComponent* Comp) override;
};
