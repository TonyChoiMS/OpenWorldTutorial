#include "Utility/SettingContainerUtils.h"
#include "UI/TCGameSettingWidget.h"
#include "Blueprint/WidgetTree.h"

TArray<UTCGameSettingWidget*> USettingContainerUtils::GetChildSettings(UUserWidget* UserWidget, UWidget* Parent)
{
	// Use widget tree so that named slots are included
	UWidgetTree* Tree = UserWidget->WidgetTree;

	TArray<UWidget*> WidgetsToTest;

	// If no parent specified, check entire tree of user widget
	if (IsValid(Parent))
	{
		Tree->GetChildWidgets(Parent, WidgetsToTest);
	}
	else
	{
		Tree->GetAllWidgets(WidgetsToTest);
	}

	TArray<UTCGameSettingWidget*> ChildSettings;

	// Filter TCSettingsWidgets
	for (UWidget* Widget : WidgetsToTest)
	{
		UTCGameSettingWidget* Setting = Cast<UTCGameSettingWidget>(Widget);
		if (Setting)
		{
			ChildSettings.Add(Setting);
		}
	}

	return ChildSettings;
}

bool USettingContainerUtils::DoesAnyChildSettingHaveUnappliedChange(UUserWidget* UserWidget, UWidget* Parent)
{
	return GetChildSettings(UserWidget, Parent).ContainsByPredicate([](UTCGameSettingWidget* Setting) { return Setting->HasUnappliedChange(); });
}

bool USettingContainerUtils::DoesAnyChildSettingHaveUnsavedChange(UUserWidget* UserWidget, UWidget* Parent)
{
	return GetChildSettings(UserWidget, Parent).ContainsByPredicate([](UTCGameSettingWidget* Setting) { return Setting->HasUnsavedChange(); });
}

void USettingContainerUtils::ApplyChildSettings(UUserWidget* UserWidget, UWidget* Parent)
{
	for (UTCGameSettingWidget* Setting : GetChildSettings(UserWidget, Parent))
	{
		Setting->Apply();
	}
}

void USettingContainerUtils::SaveChildSettings(UUserWidget* UserWidget, UWidget* Parent)
{
	for (UTCGameSettingWidget* Setting : GetChildSettings(UserWidget, Parent))
	{
		Setting->Save();
	}
}

void USettingContainerUtils::CancelChildSettings(UUserWidget* UserWidget, UWidget* Parent)
{
	for (UTCGameSettingWidget* Setting : GetChildSettings(UserWidget, Parent))
	{
		Setting->Cancel();
	}
}
