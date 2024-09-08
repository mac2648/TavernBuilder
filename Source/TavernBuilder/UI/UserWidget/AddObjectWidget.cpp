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
		PanelSlot->SetPosition(FVector2D(NewObjBntIniPosX + NewObjBntDistX * (i % NewObjBntPerRow), NewObjBntIniPosY + NewObjBntDistY * (i / NewObjBntPerRow)));
		PanelSlot->SetSize(FVector2D(NewObjBntSizeX, NewObjBntSizeY));


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

void UAddObjectWidget::MoveButtons(float Percent)
{
	for (int i = 0; i < NumNewObjBnt; i++)
	{
		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(NewObjsButtons[i]->Slot);

		PanelSlot->SetPosition(FVector2D(NewObjBntIniPosX + NewObjBntDistX * (i % NewObjBntPerRow), NewObjBntIniPosY + NewObjBntDistY * (i / NewObjBntPerRow) - Percent * NewObjUIHeight));
	}
}