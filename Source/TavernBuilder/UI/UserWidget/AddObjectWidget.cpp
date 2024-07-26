// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/UI/UserWidget/AddObjectWidget.h"
#include "Blueprint/WidgetTree.h"
#include "TavernBuilder/UI/Overlay/ObjectOptionOverlay.h"
#include "Components/CanvasPanelSlot.h"

void UAddObjectWidget::NativeConstruct()
{
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
	{
		NewObjsButtons[i] = WidgetTree->ConstructWidget<UObjectOptionOverlay>(UObjectOptionOverlay::StaticClass());

		NewObjsButtons[i]->CreateUI();

		RootWidget->AddChild(NewObjsButtons[i]);

		Cast<UCanvasPanelSlot>(NewObjsButtons[i]->Slot)->SetPosition(FVector2D(200 + 250 * (i % 5), 300 + 200 * (i / 5)));
	}
}

void UAddObjectWidget::ShowAllObjs()
{

}