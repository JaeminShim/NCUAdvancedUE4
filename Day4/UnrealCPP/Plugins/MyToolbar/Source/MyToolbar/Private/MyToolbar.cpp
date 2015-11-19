// Some copyright should be here...

#include "MyToolbarPrivatePCH.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "MyToolbarStyle.h"
#include "MyToolbarCommands.h"

#include "LevelEditor.h"



static const FName MyToolbarTabName("MyToolbar");

#define LOCTEXT_NAMESPACE "FMyToolbarModule"

void FMyToolbarModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMyToolbarStyle::Initialize();
	FMyToolbarStyle::ReloadTextures();

	FMyToolbarCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMyToolbarCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FMyToolbarModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMyToolbarModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMyToolbarModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	
}

void FMyToolbarModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
	
	
	FMyToolbarStyle::Shutdown();

	FMyToolbarCommands::Unregister();
}

void FMyToolbarModule::PluginButtonClicked()
{
	UWorld* CurrentWorld = GWorld.GetReference();
	if (CurrentWorld != nullptr)
	{
		for (TActorIterator<AActor> it(CurrentWorld); it; ++it)
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *it->GetName());
		}

		//auto Controller = UGameplayStatics::GetPlayerController(CurrentWorld, 0);
		//CurrentWorld->GetGameViewport();
	}

	//// Put your "OnButtonClicked" stuff here
	//FText DialogText = FText::Format(
	//						LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
	//						FText::FromString(TEXT("FMyToolbarModule::PluginButtonClicked()")),
	//						FText::FromString(TEXT("MyToolbar.cpp"))
	//				   );
	//FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FMyToolbarModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMyToolbarCommands::Get().PluginAction);
}

void FMyToolbarModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FMyToolbarCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyToolbarModule, MyToolbar)