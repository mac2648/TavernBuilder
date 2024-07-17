// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TavernBuilder/PlayerComponents/AddObjectComponent.h"
#include "TavernBuilder/PlayerComponents/PlaceToolComponent.h"
#include "Blueprint/UserWidget.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(ACharacter::GetMesh());
	Camera->bUsePawnControlRotation = true;

	AddObjComp = CreateDefaultSubobject<UAddObjectComponent>(TEXT("AddObjComp"));

	PlaceObjComp = CreateDefaultSubobject<UPlaceToolComponent>(TEXT("PlaceToolComp"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//deactivate all tools
	AddObjComp->Deactivate();
	PlaceObjComp->Deactivate();

	//reacivate the add tool as being the base when the game starts
	AddObjComp->Activate();

	//creates the choose tools widget
	ChooseToolWidget = CreateWidget<UUserWidget>(Cast<APlayerController>(GetController()), ChooseToolWidgetClass);
	if (ChooseToolWidget)
	{
		ChooseToolWidget->AddToViewport();
		ChooseToolWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(OpenChooseToolWidgetAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OpenCloseChooseToolWidget);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Initialize PLayer input"))
	}

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator ControllerRotation = Controller->GetControlRotation();

		FRotator YawRotation(0, ControllerRotation.Yaw, 0);

		const FVector FowardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(FowardVector, MoveVector.X);
		AddMovementInput(RightVector, MoveVector.Y);

	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxis = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxis.X);
		AddControllerPitchInput(LookAxis.Y);
	}
}

void APlayerCharacter::OpenCloseChooseToolWidget(const FInputActionValue& Value)
{
	bool Open = Value.Get<bool>();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (Open)
		{
			PlayerController->SetInputMode(FInputModeGameAndUI());
			if (ChooseToolWidget)
			{
				ChooseToolWidget->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			PlayerController->SetInputMode(FInputModeGameOnly());
			if (ChooseToolWidget)
			{
				ChooseToolWidget->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void APlayerCharacter::ActivateTool(ETools Tool)
{
	if (Tool == CurrentTool)
	{
		return;
	}

	switch (CurrentTool)
	{
	case ADD:
		AddObjComp->Deactivate();
		break;
	case MOVE:
		PlaceObjComp->Deactivate();
		break;
	case DELETE:
		break;
	case PAINT:
		break;
	case CHANGE_DESIGN:
		break;
	case CLEAN:
		break;
	case GARBAGE:
		break;
	default:
		break;
	}

	switch (Tool)
	{
	case ADD:
		AddObjComp->Activate();
		break;
	case MOVE:
		PlaceObjComp->Activate();
		break;
	case DELETE:
		break;
	case PAINT:
		break;
	case CHANGE_DESIGN:
		break;
	case CLEAN:
		break;
	case GARBAGE:
		break;
	default:
		break;
	}

	CurrentTool = Tool;
}