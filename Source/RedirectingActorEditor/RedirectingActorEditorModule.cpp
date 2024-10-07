#include "RedirectingActorEditorModule.h"
#include "EditorModeRegistry.h"
#include "RedirectingActorEditor/EditorMode/RedirectingActorMode.h"

void FRedirectingActorEditorModule::StartupModule()
{
    FEditorModeRegistry::Get().RegisterMode<FRedirectingActorMode>(
        FRedirectingActorMode::EM_RedirectingActorMode,
        FText::FromString("RedirectingActorEditor"),
        FSlateIcon(),
        true);
}

void FRedirectingActorEditorModule::ShutdownModule()
{
    IModuleInterface::ShutdownModule();
    // Unregister the custom editor mode here
    FEditorModeRegistry::Get().UnregisterMode(FRedirectingActorMode::EM_RedirectingActorMode);
}

IMPLEMENT_MODULE(FRedirectingActorEditorModule, RedirectingActorEditor)