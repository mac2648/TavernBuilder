#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"

class FRedirectingActorMode : public FEdMode
{

public:
	const static inline FEditorModeID EM_RedirectingActorMode = TEXT("EM_RedirectingActorMode");

public:
	FRedirectingActorMode();
	virtual ~FRedirectingActorMode();

	virtual bool Select(AActor* InActor, bool bInSelected) override;
};