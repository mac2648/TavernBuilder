#include "ObjectPreviewButtonModule/Button/ObjectPreviewButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "Components/OverlaySlot.h"


void UObjectPreviewButton::SetInfo(const FObjectPreviewInfo* NewInfo)
{
	if (Info)
	{
		*Info = *NewInfo;
	}

	if (!(Info->Name.IsEmpty()))
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

void UObjectPreviewButton::ClearInfo()
{
	Info->Clear();

	Text->SetText(FText::FromString(""));

	Image->SetBrushFromTexture(Info->Image);
}

void UObjectPreviewButton::CreateUI()
{
	Image = NewObject<UImage>(this);
	if (Image)
	{
		AddChild(Image);

		Image->Brush.ImageSize.X = ImageSize.X;
		Image->Brush.ImageSize.Y = ImageSize.Y;

		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(Image->Slot))
		{
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Bottom);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		}
	}

	Text = NewObject<UTextBlock>(this);
	if (Text)
	{
		AddChild(Text);

		Text->SetColorAndOpacity(FSlateColor(FColor::Black));

		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(Text->Slot))
		{
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Top);
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

		Button->OnClicked.AddDynamic(this, &UObjectPreviewButton::OptionButtonClick);
	}
}

void UObjectPreviewButton::OptionButtonClick()
{
	OnOptionButtonClick.Broadcast(this);
}