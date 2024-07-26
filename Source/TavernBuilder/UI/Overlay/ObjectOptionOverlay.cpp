// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/UI/Overlay/ObjectOptionOverlay.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"

void UObjectOptionOverlay::SetInfo(FObjOptionButtonInfo& NewInfo)
{
	Info = NewInfo;

	Text->SetText(Info.Name);
}

void UObjectOptionOverlay::CreateUI()
{
	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Slot))
	{
		CanvasSlot->SetSize(FVector2D(250, 250));
	}

	Button = NewObject<UButton>(this);
	if (Button)
	{
		AddChild(Button);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Button->Slot))
		{
			CanvasSlot->SetSize(FVector2D(250, 150));
			CanvasSlot->SetPosition(FVector2D(0, 100));
		}
	}

	Text = NewObject<UTextBlock>(this);
	if (Text)
	{
		AddChild(Text);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Text->Slot))
		{
			CanvasSlot->SetSize(FVector2D(250, 100));
			CanvasSlot->SetPosition(FVector2D(0, 0));
		}
	}
}