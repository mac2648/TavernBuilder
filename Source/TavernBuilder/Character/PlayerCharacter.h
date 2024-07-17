// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAddObjectComponent;
class UPlaceToolComponent;

UENUM(BlueprintType)
enum ETools
{
	ADD,
	MOVE,
	DELETE,
	PAINT,
	CHANGE_DESIGN,
	CLEAN,
	GARBAGE
};

UCLASS()
class TAVERNBUILDER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputAction* OpenChooseToolWidgetAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAddObjectComponent* AddObjComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPlaceToolComponent* PlaceObjComp;

	UPROPERTY(EditDefaultsOnly, category = "UI")
	TSubclassOf<UUserWidget> ChooseToolWidgetClass;

	UUserWidget* ChooseToolWidget = nullptr;

	ETools CurrentTool = ADD;

public:
	APlayerCharacter();

	UFUNCTION(BlueprintCallable)
	inline ETools GetCurrentTool() const { return CurrentTool; }

	UFUNCTION(BlueprintCallable)
	void ActivateTool(ETools Tool);

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return Camera; }

	/*do not use this function to Activate or Deactivate the component
	all components must be activated or deactivated by the function ActivateTool*/
	inline UPlaceToolComponent* GetPlaceToolComp() const { return PlaceObjComp; }

protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void OpenCloseChooseToolWidget(const FInputActionValue& Value);
};
