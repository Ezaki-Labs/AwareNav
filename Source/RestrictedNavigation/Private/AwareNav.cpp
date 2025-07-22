#include "AwareNav.h"

#include "AwareNavSettings.h"
#include "ISettingsModule.h"

#define LOCTEXT_NAMESPACE "FAwareNavModule"

void FAwareNavModule::StartupModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project",
			"Plugins",
			"AwareNav",
			FText::FromString("AwareNav"),
			FText::FromString("Configure navigation behavior for permissions and emotion."),
			GetMutableDefault<UAwareNavSettings>()
		);
	}
}

void FAwareNavModule::ShutdownModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "AwareNav");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAwareNavModule, AwareNav)