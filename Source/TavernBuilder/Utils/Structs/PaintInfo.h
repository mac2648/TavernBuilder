#pragma once

#include "CoreMinimal.h"
#include "PaintInfo.generated.h"

USTRUCT(BlueprintType)
struct FPaintInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* Material;
};

UCLASS(config = Game, BlueprintType, Blueprintable, MinimalAPI)
class UPaintInfoList : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TArray<FPaintInfo> List;
};