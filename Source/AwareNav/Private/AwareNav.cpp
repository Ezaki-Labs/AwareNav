#include "AwareNav.h"

#include "AwareNavSettings.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#endif

#define LOCTEXT_NAMESPACE "FAwareNavModule"

void FAwareNavModule::StartupModule()
{
#if WITH_EDITOR
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
#endif
}

void FAwareNavModule::ShutdownModule()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "AwareNav");
	}
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAwareNavModule, AwareNav)