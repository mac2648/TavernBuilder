// Fill out your copyright notice in the Description page of Project Settings.


#include "TavernBuilder/UI/UserWidget/AddObjectWidget.h"
#include "Blueprint/WidgetTree.h"
#include "TavernBuilder/UI/Overlay/ObjectOptionOverlay.h"
#include "Components/CanvasPanelSlot.h"
#include "TavernBuilder/PlayerComponents/AddObjectComponent.h"
#include "Components/Button.h"
#include "InputActionValue.h"
#include "TavernBuilder/Utils/TavernBuilderUtils.h"
#include "Components/Slider.h"
#include "TavernBuilder/UI/Overlay/ChooseObjCategoryOverlay.h"

void UAddObjectWidget::NativeConstruct()
{
	ObjButtonClass = TSubclassOf<UObjectPreviewButton>(UObjectOptionOverlay::StaticClass());
	ObjButtons = new UObjectPreviewButton*[NumNewObjBnt];
	NumObjButtons = NumNewObjBnt;

	TextButtonClass = TSubclassOf<UTextButton>(UChooseObjCategoryOverlay::StaticClass());
	TextButtons = new UTextButton*[AllCategories + 1];
	NumTextButtons = AllCategories + 1;

	ObjBntIniPos = FVector2D(NewObjBntIniPosX, NewObjBntIniPosY);
	ObjBntDis = FVector2D(NewObjBntDistX, NewObjBntDistY);
	ObjBntSize = FVector2D(NewObjBntSizeX, NewObjBntSizeY);

	TextBntIntPos = FVector2D(CatBntPosX, CatBntPosY);
	TextBntDistanceY = CatBntDisY;
	TextBntSize = FVector2D(CategoryBntSizeX, CategoryBntSizeY);

	SliderSize = FVector2D(NewObjSliderWidth, NewObjSliderHeight);
	NumObjPerRow = NewObjBntPerRow;

	Super::NativeConstruct();

	for (EObjectCategory i = EObjectCategory::Chair; i <= AllCategories; i++)
	{
		if (UChooseObjCategoryOverlay* CategoryButton = Cast<UChooseObjCategoryOverlay>(TextButtons[i]))
		{
			CategoryButton->SetCategory(i);
			FText CategoryText = FText::FromString(UTavernBuilderUtils::GetObjCategoryName(i));
			CategoryButton->SetText(CategoryText);
		}
	}
}

void UAddObjectWidget::ShowAllObjs()
{
	ApplyCatagory(Cast<UChooseObjCategoryOverlay>(TextButtons[AllCategories]));
}

void UAddObjectWidget::ButtonClick(UObjectPreviewButton* PressedButton)
{
	if (UObjectOptionOverlay* PressedBnt = Cast<UObjectOptionOverlay>(PressedButton))
	{
		AddObjComp->SetObjectClass(PressedBnt->GetObjectClass());
		AddObjComp->SetObjectType(PressedBnt->GetObjectType());
		AddObjComp->Execute(FInputActionValue());
	}
}

void UAddObjectWidget::ApplyTextButton(UTextButton* ClickedOverlay)
{
	ApplyCatagory(Cast<UChooseObjCategoryOverlay>(ClickedOverlay));
}

void UAddObjectWidget::ApplyCatagory(UChooseObjCategoryOverlay* ClickedOverlay)
{
	for (int i = 0; i < NumNewObjBnt; i++)
	{
		ObjButtons[i]->ClearInfo();
		ObjButtons[i]->SetVisibility(ESlateVisibility::Visible);
	}

	TArray<FObjectInfo> List; 
	AddObjComp->GetPlaceableObjectsListByCategory(ClickedOverlay->GetCategory(), List);

	for (int i = 0; i < List.Num() && i < NumNewObjBnt; i++)
	{
		FObjOptionButtonInfo ObjInfo = FObjOptionButtonInfo(List[i]);
		ObjButtons[i]->SetInfo(&ObjInfo);
	}

	NumActiveButtons = List.Num();

	for (int i = 0; i < NumNewObjBnt; i++)
	{
		if (!(ObjButtons[i]->IsValid()))
		{
			ObjButtons[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	Slider->SetValue(0.0f);
}