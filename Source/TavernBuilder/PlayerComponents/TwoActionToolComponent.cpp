// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/PlayerComponents/TwoActionToolComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "TavernBuilder/Character/PlayerCharacter.h"

void UTwoActionToolComponent::OnActivate(UActorComponent* Comp, bool IsReset)
{
	Super::OnActivate(Comp, IsReset);

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player->InputComponent))
		{
			SecondaryActionBind = &EnhancedInputComponent->BindAction(SecondaryInputAction, ETriggerEvent::Triggered, this, &UTwoActionToolComponent::SecondaryExecute);
		}
	}
}

void UTwoActionToolComponent::OnDeactivate(UActorComponent* Comp)
{
	Super::OnDeactivate(Comp);

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player->InputComponent))
		{
			if (SecondaryActionBind)
			{
				EnhancedInputComponent->RemoveBinding(*SecondaryActionBind);
			}
		}
	}
}

void UTwoActionToolComponent::SecondaryExecute(const FInputActionValue& Value)
{

}