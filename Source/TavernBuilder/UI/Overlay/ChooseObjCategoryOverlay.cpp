// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/UI/Overlay/ChooseObjCategoryOverlay.h"
#include "Components/Button.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"
#include "TavernBuilder/Utils/TavernBuilderUtils.h"

void UChooseObjCategoryOverlay::Initialize(EObjectCategory NewCategory)
{
	Category = NewCategory;

	CategoryButton = NewObject<UButton>();

	if (CategoryButton)
	{
		AddChild(CategoryButton);

		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(CategoryButton->Slot))
		{
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		}
	}

	CategoryText = NewObject<UTextBlock>();

	if (CategoryText)
	{
		AddChild(CategoryText);

		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(CategoryText->Slot))
		{
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		}

		CategoryText->SetText(FText::FromString(UTavernBuilderUtils::GetObjCategoryName(Category)));
		CategoryText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}