// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/UI/UserWidget/AddObjectWidget.h"
#include "Blueprint/WidgetTree.h"
#include "TavernBuilder/UI/Overlay/ObjectOptionOverlay.h"
#include "Components/CanvasPanelSlot.h"
#include "TavernBuilder/PlayerComponents/AddObjectComponent.h"
#include "Components/Button.h"
#include "InputActionValue.h"

void UAddObjectWidget::NativeConstruct()
{
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	for (int i = 0; i < NumNewObjBnt; i++)
	{
		NewObjsButtons[i] = WidgetTree->ConstructWidget<UObjectOptionOverlay>(UObjectOptionOverlay::StaticClass());

		RootWidget->AddChild(NewObjsButtons[i]);

		Cast<UCanvasPanelSlot>(NewObjsButtons[i]->Slot)->SetPosition(FVector2D(200 + NewObjBntDistX * (i % NewObjBntPerRow), 300 + NewObjBntDistY * (i / NewObjBntPerRow)));
		Cast<UCanvasPanelSlot>(NewObjsButtons[i]->Slot)->SetSize(FVector2D(NewObjBntSizeX, NewObjBntSizeY));

		NewObjsButtons[i]->CreateUI();

		NewObjsButtons[i]->OnOptionButtonClick.AddDynamic(this, &UAddObjectWidget::ButtonClick);
	}
}

void UAddObjectWidget::ShowAllObjs()
{
	const TArray<FObjectInfo>& List = AddObjComp->GetPlaceableObjectsList();

	for (int i = 0; i < List.Num() && i < NumNewObjBnt; i++)
	{
		NewObjsButtons[i]->SetInfo(List[i]);
	}
}

void UAddObjectWidget::ButtonClick(UObjectOptionOverlay* PressedButton)
{
	AddObjComp->SetObjectClass(PressedButton->GetObjectClass());
	AddObjComp->Execute(FInputActionValue());
}