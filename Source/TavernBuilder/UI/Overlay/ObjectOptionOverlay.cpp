// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/UI/Overlay/ObjectOptionOverlay.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "Components/OverlaySlot.h"

void UObjectOptionOverlay::SetInfo(const FObjOptionButtonInfo& NewInfo)
{
	Info = NewInfo;

	Text->SetText(Info.Name);
	if (Info.Image)
	{
		Image->SetBrushFromTexture(Info.Image);
	}
}

void UObjectOptionOverlay::CreateUI()
{
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

	Image = NewObject<UImage>(this);
	if (Image)
	{
		AddChild(Image);

		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(Image->Slot))
		{
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Bottom);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		}
	}

	Button = NewObject<UButton>(this);
	if (Button)
	{
		AddChild(Button);

		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(Button->Slot))
		{
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		}

		FButtonStyle ButtonStyle = Button->GetStyle();
		ButtonStyle.Normal.TintColor = FSlateColor(FColor(1, 1, 1, 0));
		ButtonStyle.Hovered.TintColor = FSlateColor(FColor(1, 1, 1, 0.1));
		ButtonStyle.Pressed.TintColor = FSlateColor(FColor(1, 1, 1, 0.2));
		Button->SetStyle(ButtonStyle);

		Button->OnClicked.AddDynamic(this, &UObjectOptionOverlay::OptionButtonClick);
	}
}

void UObjectOptionOverlay::OptionButtonClick()
{
	OnOptionButtonClick.Broadcast(this);
}