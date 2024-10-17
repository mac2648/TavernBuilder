#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectPreviewWidget.generated.h"

class UObjectPreviewButton;
class UObjectOptionOverlay;
class USlider;
class UTextButton;


UCLASS()
class OBJECTPREVIEWBUTTONMODULE_API UObjectPreviewWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	TSubclassOf<UObjectPreviewButton> ObjButtonClass;
	//give it a size on construction of child class
	UObjectPreviewButton** ObjButtons = nullptr;
	//initialize this number to be the same as ObjButtons Size
	int NumObjButtons = 0;

	USlider* Slider;

	TSubclassOf<UTextButton> TextButtonClass;
	//give it a size on construction of child class
	UTextButton** TextButtons;
	//initialize this number to be the same as TextButtons Size
	int NumTextButtons = 0;

	FVector2D ObjBntIniPos = FVector2D(0, 0);
	FVector2D ObjBntDis = FVector2D(0, 0);
	FVector2D ObjBntSize = FVector2D(0, 0);

	FVector2D TextBntIntPos = FVector2D(0, 0);
	float TextBntDistanceY = 0.0f;
	FVector2D TextBntSize = FVector2D(0, 0);

	FVector2D SliderSize = FVector2D(0, 0);
	int NumObjPerRow = 1;

	int NumActiveButtons = 0;

	inline int NewObjUIHeight(int NUM_ACTIVE_OBJ) { return ObjBntDis.Y * FMath::CeilToInt(float(NUM_ACTIVE_OBJ) / float(NumObjPerRow) - 2.0); }

public:

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void MoveButtons(float Percent);

	UFUNCTION()
	virtual void ButtonClick(UObjectPreviewButton* PressedButton) {};

	UFUNCTION()
	virtual void ApplyTextButton(UTextButton* ClickedOverlay) {};
};