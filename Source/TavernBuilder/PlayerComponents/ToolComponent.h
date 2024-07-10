// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToolComponent.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FInputBindingHandle;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAVERNBUILDER_API UToolComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputMappingContext* ToolMappingContext;

	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputAction* PrimaryInputAction;
	FInputBindingHandle* PrimaryActionBind;

public:	
	UToolComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnActivate(UActorComponent* Comp, bool IsReset);

	UFUNCTION()
	virtual void OnDeactivate(UActorComponent* Comp);

	virtual void Execute(const FInputActionValue& Value);
};
