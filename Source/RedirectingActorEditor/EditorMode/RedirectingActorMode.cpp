#include "RedirectingActorEditor/EditorMode/RedirectingActorMode.h"
#include "EditorModeRegistry.h"
#include "RedirectingActorEditor/EditorMode/RedirectingActorInterface.h"

FRedirectingActorMode::FRedirectingActorMode()
{

}

FRedirectingActorMode::~FRedirectingActorMode()
{

}

bool FRedirectingActorMode::Select(AActor* InActor, bool bInSelected)
{
	#if WITH_EDITOR
	if (IRedirectingActorInterface* Interface = Cast<IRedirectingActorInterface>(InActor))
	{
		if (AActor* RedirectActor = Interface->GetObjOwner())
		{
			FTimerDelegate Func;
			Func.BindLambda([RedirectActor, this]() 
			{

				GEditor->SelectNone(false, true);
				GEditor->NoteSelectionChange();

				FTimerDelegate FuncSelect;
				FuncSelect.BindLambda([RedirectActor]() 
				{
					GEditor->SelectActor(RedirectActor, true, false, true);
					GEditor->NoteSelectionChange(); 
				});

				GetWorld()->GetTimerManager().SetTimerForNextTick(FuncSelect);
			});
				
			
			GetWorld()->GetTimerManager().SetTimerForNextTick(Func);
		}
	}
	#endif

	return 0;
}