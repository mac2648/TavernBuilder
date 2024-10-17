#include "TextButton.h"
#include "Components/Button.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"

void UTextButton::Initialize()
{
	Button = NewObject<UButton>();

	if (Button)
	{
		AddChild(Button);

		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(Button->Slot))
		{
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		}

		Button->OnClicked.AddDynamic(this, &UTextButton::TextButtonClick);
	}

	Text = NewObject<UTextBlock>();

	if (Text)
	{
		AddChild(Text);

		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(Text->Slot))
		{
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		}

		//CategoryText->SetText(FText::FromString(UTavernBuilderUtils::GetObjCategoryName(Category)));
		Text->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UTextButton::TextButtonClick()
{
	OnTextButtonClick.Broadcast(this);
}

void UTextButton::SetText(FText& NewText)
{
	Text->SetText(NewText);
}