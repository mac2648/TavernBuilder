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
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	Slider = WidgetTree->ConstructWidget<USlider>();

	if (Slider)
	{
		RootWidget->AddChild(Slider);

		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Slider->Slot);

		PanelSlot->SetAnchors(FAnchors(0.5, 0.5));
		PanelSlot->SetPosition(FVector2D(NewObjBntIniPosX + NewObjBntPerRow * NewObjBntDistX + 100, NewObjBntIniPosY));
		PanelSlot->SetSize(FVector2D(NewObjSliderWidth, NewObjSliderHeight));

		Slider->SetOrientation(EOrientation::Orient_Vertical);

		FSliderStyle Style = Slider->GetWidgetStyle();
		Style.SetBarThickness(NewObjSliderWidth);
		Slider->SetWidgetStyle(Style);

		FWidgetTransform Transform = Slider->GetRenderTransform();
		Transform.Angle = 180.0f;
		Slider->SetRenderTransform(Transform);

		Slider->OnValueChanged.AddDynamic(this, &UAddObjectWidget::MoveButtons);

	}

	for (int i = 0; i < NumNewObjBnt; i++)
	{
		NewObjsButtons[i] = WidgetTree->ConstructWidget<UObjectOptionOverlay>(UObjectOptionOverlay::StaticClass());

		RootWidget->AddChild(NewObjsButtons[i]);

		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(NewObjsButtons[i]->Slot);

		PanelSlot->SetAnchors(FAnchors(0.5, 0.5));

		int NewObkButtonPositionX = NewObjBntIniPosX + NewObjBntDistX * (i % NewObjBntPerRow);
		int NewObkButtonPositionY = NewObjBntIniPosY + NewObjBntDistY * (i / NewObjBntPerRow);

		PanelSlot->SetPosition(FVector2D(NewObkButtonPositionX, NewObkButtonPositionY));
		PanelSlot->SetSize(FVector2D(NewObjBntSizeX, NewObjBntSizeY));

		NewObjsButtons[i]->CreateUI();

		NewObjsButtons[i]->OnOptionButtonClick.AddDynamic(this, &UAddObjectWidget::ButtonClick);
	}

	for (EObjectCategory i = EObjectCategory::Chair; i <= AllCategories; i++)
	{
		Categories[i] = WidgetTree->ConstructWidget<UChooseObjCategoryOverlay>();

		RootWidget->AddChild(Categories[i]);

		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Categories[i]->Slot);

		PanelSlot->SetAnchors(FAnchors(0.5, 0.5));
		PanelSlot->SetPosition(FVector2D(CatBntPosX, CatBntPosY + (CatBntDisY * i) ));
		PanelSlot->SetSize(FVector2D(CategoryBntSizeX, CategoryBntSizeY));

		Categories[i]->Initialize(i);

		Categories[i]->OnCategoryClick.AddDynamic(this, &UAddObjectWidget::ApplyCatagory);
	}
}

void UAddObjectWidget::ShowAllObjs()
{
	ApplyCatagory(Categories[AllCategories]);
}

void UAddObjectWidget::ButtonClick(UObjectOptionOverlay* PressedButton)
{
	AddObjComp->SetObjectClass(PressedButton->GetObjectClass());
	AddObjComp->Execute(FInputActionValue());
}

void UAddObjectWidget::MoveButtons(float Percent)
{
	for (int i = 0; i < NumNewObjBnt; i++)
	{
		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(NewObjsButtons[i]->Slot);

		int UIHeight = NewObjUIHeight(NumActiveButtons);
		if (UIHeight <= 0)
		{
			UIHeight = 0;
		}

		PanelSlot->SetPosition(FVector2D(NewObjBntIniPosX + NewObjBntDistX * (i % NewObjBntPerRow), NewObjBntIniPosY + NewObjBntDistY * (i / NewObjBntPerRow) - Percent * UIHeight));
	}
}

void UAddObjectWidget::ApplyCatagory(UChooseObjCategoryOverlay* ClickedOverlay)
{
	for (int i = 0; i < NumNewObjBnt; i++)
	{
		NewObjsButtons[i]->ClearInfo();
		NewObjsButtons[i]->SetVisibility(ESlateVisibility::Visible);
	}

	TArray<FObjectInfo> List; 
	AddObjComp->GetPlaceableObjectsListByCategory(ClickedOverlay->GetCategory(), List);

	for (int i = 0; i < List.Num() && i < NumNewObjBnt; i++)
	{
		NewObjsButtons[i]->SetInfo(List[i]);
	}

	NumActiveButtons = List.Num() + 1;

	for (int i = 0; i < NumNewObjBnt; i++)
	{
		if (!NewObjsButtons[i]->IsValid())
		{
			NewObjsButtons[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	Slider->SetValue(0.0f);
}