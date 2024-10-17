#pragma once

#include "CoreMinimal.h"
#include "Components/Overlay.h"
#include "ObjectPreviewButtonModule/Struct/ObjectPreviewInfo.h"
#include "ObjectPreviewButton.generated.h"


class APlaceableObjects;
class UTextBlock;
class UButton;
class UImage;
enum EObjectType;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventButtonClick, UObjectPreviewButton*, ClickedOverlay);

UCLASS()
class OBJECTPREVIEWBUTTONMODULE_API UObjectPreviewButton : public UOverlay
{
	GENERATED_BODY()

protected:

	FVector2D ImageSize = FVector2D(0, 0);

	struct FObjectPreviewInfo* Info;

	UTextBlock* Text;

	UButton* Button;

	UImage* Image;

public:
	virtual void SetInfo(const FObjectPreviewInfo* NewInfo);
	void ClearInfo();

	void CreateUI();

	bool IsValid() const { return Info->IsValid(); }

	FEventButtonClick OnOptionButtonClick;

protected:
	UFUNCTION()
	void OptionButtonClick();
};