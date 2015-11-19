// Some copyright should be here...

#pragma once

#include "SlateBasics.h"
#include "MyToolbarStyle.h"

class FMyToolbarCommands : public TCommands<FMyToolbarCommands>
{
public:

	FMyToolbarCommands()
		: TCommands<FMyToolbarCommands>(TEXT("MyToolbar"), NSLOCTEXT("Contexts", "MyToolbar", "MyToolbar Plugin"), NAME_None, FMyToolbarStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
