// Fill out your copyright notice in the Description page of Project Settings.

#include "TavernBuilder/PlayerComponents/ToolComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "TavernBuilder/Character/PlayerCharacter.h"

#define GET_PLAYER_CONTROLLER Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController())
#define GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GET_PLAYER_CONTROLLER->GetLocalPlayer())


// Sets default values for this component's properties
UToolComponent::UToolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UToolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OnComponentActivated.AddDynamic(this, &UToolComponent::OnActivate);
	OnComponentDeactivated.AddDynamic(this, &UToolComponent::OnDeactivate);

	OnActivate(this, false);
}


// Called every frame
void UToolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UToolComponent::OnActivate(UActorComponent* Comp, bool IsReset)
{
	UEnhancedInputLocalPlayerSubsystem* SubSystem = GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM;

	if (SubSystem)
	{
		SubSystem->AddMappingContext(ToolMappingContext, 1);
	}

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player->InputComponent))
		{
			PrimaryActionBind = &EnhancedInputComponent->BindAction(PrimaryInputAction, ETriggerEvent::Triggered, this, &UToolComponent::Execute);
		}
	}
}

void UToolComponent::OnDeactivate(UActorComponent* Comp)
{
	UEnhancedInputLocalPlayerSubsystem* SubSystem = GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM;

	if (SubSystem)
	{
		SubSystem->RemoveMappingContext(ToolMappingContext);
	}

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player->InputComponent))
		{
			EnhancedInputComponent->RemoveBinding(*PrimaryActionBind);
		}
	}
}

void UToolComponent::Execute(const FInputActionValue& Value)
{

}