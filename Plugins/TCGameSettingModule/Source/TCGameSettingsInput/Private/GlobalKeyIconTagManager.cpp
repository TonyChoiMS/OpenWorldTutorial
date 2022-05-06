
#include "GlobalKeyIconTagManager.h"

#include "InputMappingManager.h"
#include "Misc/ITCGameSettingsInputConfig.h"

UGlobalKeyIconTagManager* UGlobalKeyIconTagManager::Singleton = nullptr;

UGlobalKeyIconTagManager* UGlobalKeyIconTagManager::Get()
{
	if (!Singleton)
	{
		Singleton = NewObject<UGlobalKeyIconTagManager>();
		Singleton->AddToRoot();
	}

	return Singleton;
}

void UGlobalKeyIconTagManager::SetGlobalKeyIconTags(FGameplayTagContainer InGlobalIconTags)
{
	if (Get()->GlobalKeyIconTags != InGlobalIconTags)
	{
		Get()->GlobalKeyIconTags = InGlobalIconTags;
		Get()->OnGlobalKeyIconTagsModified.Broadcast();
	}
}

UTexture* UGlobalKeyIconTagManager::GetIconForKey(FKey InKey, FGameplayTagContainer IconTags, float AxisScale)
{
	IconTags.AppendTags(Get()->GlobalKeyIconTags);
	return UInputMappingManager::GetInputConfigStatic()->GetIconForKey(InKey, IconTags, AxisScale);
}
