#include "Utility/TCGameSettingsStringUtils.h"

bool FTCGameSettingsStringUtils::IsTruthy(const FString& String)
{
	return String != "0" && String.ToLower() != "false";
}