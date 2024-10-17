#include "ObjectPreviewWidget.h"
#include "ObjectPreviewButtonModule/Button/ObjectPreviewButton.h"
#include "ObjectPreviewButtonModule/Button/TextButton.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "Components/Slider.h"


void UObjectPreviewWidget::NativeConstruct()
{
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	Slider = WidgetTree->ConstructWidget<USlider>();

	if (Slider)
	{
		RootWidget->AddChild(Slider);

		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Slider->Slot);

		PanelSlot->SetAnchors(FAnchors(0.5, 0.5));
		PanelSlot->SetPosition(FVector2D(ObjBntIniPos.X + NumObjPerRow * ObjBntDis.X + 100, ObjBntIniPos.Y));
		PanelSlot->SetSize(FVector2D(SliderSize.X, SliderSize.Y));

		Slider->SetOrientation(EOrientation::Orient_Vertical);

		FSliderStyle Style = Slider->GetWidgetStyle();
		Style.SetBarThickness(SliderSize.X);
		Slider->SetWidgetStyle(Style);

		FWidgetTransform Transform = Slider->GetRenderTransform();
		Transform.Angle = 180.0f;
		Slider->SetRenderTransform(Transform);

		Slider->OnValueChanged.AddDynamic(this, &UObjectPreviewWidget::MoveButtons);

	}

	for (int i = 0; i < NumObjButtons; i++)
	{
		ObjButtons[i] = WidgetTree->ConstructWidget<UObjectPreviewButton>(ObjButtonClass);

		RootWidget->AddChild(ObjButtons[i]);

		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(ObjButtons[i]->Slot);

		PanelSlot->SetAnchors(FAnchors(0.5, 0.5));

		int NewObkButtonPositionX = ObjBntIniPos.X + ObjBntDis.X * (i % NumObjPerRow);
		int NewObkButtonPositionY = ObjBntIniPos.Y + ObjBntDis.Y * (i / NumObjPerRow);

		PanelSlot->SetPosition(FVector2D(NewObkButtonPositionX, NewObkButtonPositionY));
		PanelSlot->SetSize(FVector2D(ObjBntSize.X, ObjBntSize.Y));

		ObjButtons[i]->CreateUI();

		ObjButtons[i]->OnOptionButtonClick.AddDynamic(this, &UObjectPreviewWidget::ButtonClick);
	}

	for (int i = 0; i < NumTextButtons; i++)
	{
		TextButtons[i] = WidgetTree->ConstructWidget<UTextButton>(TextButtonClass);

		RootWidget->AddChild(TextButtons[i]);

		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(TextButtons[i]->Slot);

		PanelSlot->SetAnchors(FAnchors(0.5, 0.5));
		PanelSlot->SetPosition(FVector2D(TextBntIntPos.X, TextBntIntPos.Y + (TextBntDistanceY * i)));
		PanelSlot->SetSize(FVector2D(TextBntSize.X, TextBntSize.Y));

		TextButtons[i]->Initialize();

		TextButtons[i]->OnTextButtonClick.AddDynamic(this, &UObjectPreviewWidget::ApplyTextButton);
	}
}

void UObjectPreviewWidget::MoveButtons(float Percent)
{
	for (int i = 0; i < NumObjButtons; i++)
	{
		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(ObjButtons[i]->Slot);

		int UIHeight = NewObjUIHeight(NumActiveButtons);
		if (UIHeight <= 0)
		{
			UIHeight = 0;
		}

		PanelSlot->SetPosition(FVector2D(ObjBntIniPos.X + ObjBntDis.X * (i % NumObjPerRow), ObjBntIniPos.Y + ObjBntDis.Y * (i / NumObjPerRow) - Percent * UIHeight));
	}
}