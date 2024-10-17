#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RedirectingActorInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class URedirectingActorInterface : public UInterface
{
	GENERATED_BODY()
};

class IRedirectingActorInterface
{
	GENERATED_BODY()

protected:
	AActor* ObjOwner;

public:
	void SetObjOwner(AActor* NewOwner) { ObjOwner = NewOwner; }
	AActor* GetObjOwner() const { return ObjOwner; }
};