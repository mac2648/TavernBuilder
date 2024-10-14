#pragma once

#pragma once

#include "CoreMinimal.h"
#include "Components/Overlay.h"
#include "TextButton.generated.h"

class UButton;
class UTextBlock;
enum EObjectCategory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventTextButtonClick, UTextButton*, ClickedOverlay);


UCLASS()
class OBJECTPREVIEWBUTTONMODULE_API UTextButton : public UOverlay
{
	GENERATED_BODY()

public:
	FEventTextButtonClick OnTextButtonClick;

private:

	UButton* Button = nullptr;

	UTextBlock* Text = nullptr;


public:
	void Initialize();
	void SetText(FText& NewText);

private:
	UFUNCTION()
	void TextButtonClick();
};
