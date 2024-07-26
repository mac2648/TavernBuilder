// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/UI/Overlay/ObjectOptionOverlay.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Components/OverlaySlot.h"

void UObjectOptionOverlay::SetInfo(const FObjOptionButtonInfo& NewInfo)
{
	Info = NewInfo;

	Text->SetText(Info.Name);
}

void UObjectOptionOverlay::CreateUI()
{
	Button = NewObject<UButton>(this);
	if (Button)
	{
		AddChild(Button);

		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(Button->Slot))
		{
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Bottom);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		}
	}

	Text = NewObject<UTextBlock>(this);
	if (Text)
	{
		AddChild(Text);

		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(Text->Slot))
		{
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Top);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		}
	}
}