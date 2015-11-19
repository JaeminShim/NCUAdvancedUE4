// Some copyright should be here...

#include "MyToolbarPrivatePCH.h"
#include "MyToolbarCommands.h"

#define LOCTEXT_NAMESPACE "FMyToolbarModule"

void FMyToolbarCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "MyToolbar", "Execute MyToolbar action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
