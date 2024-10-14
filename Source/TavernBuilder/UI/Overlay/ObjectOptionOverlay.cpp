// Fill out your copyright notice in the Description page of Project Settings.

#include "TavernBuilder/UI/Overlay/ObjectOptionOverlay.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "Components/OverlaySlot.h"
#include "TavernBuilder/Utils/Consts/ConstsUI.h"
#include <exception>

UObjectOptionOverlay::UObjectOptionOverlay()
{
	Info = new FObjOptionButtonInfo();
	ImageSize.X = NewObjImgSizeX;
	ImageSize.Y = NewObjImgSizeY;
}

void UObjectOptionOverlay::SetInfo(const FObjectPreviewInfo* NewInfo)
{
	const FObjOptionButtonInfo* NewInfoCasted = static_cast<const FObjOptionButtonInfo*>(NewInfo);
	if (!NewInfoCasted)
	{
		throw("expected FObjOptionButtonInfo, but received something else");
	}

	if (FObjOptionButtonInfo* CastedInfo = static_cast<FObjOptionButtonInfo*>(Info))
	{
		*CastedInfo = *NewInfoCasted;
	}
	else
	{
		throw("expected info to be FObjOptionButtonInfo, but static cast failed");
	}

	if (!Info->Name.IsEmpty())
	{
		FString Temp = Info->Name;

		Text->SetText(FText::FromString(Temp));
	}
	else
	{
		Text->SetText(FText::FromString(""));
	}

	if (Info->Image)
	{
		Image->SetBrushFromTexture(Info->Image);
	}
}