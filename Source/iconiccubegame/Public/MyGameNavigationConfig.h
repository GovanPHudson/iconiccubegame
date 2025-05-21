#pragma once

#include "CoreMinimal.h"
#include "Framework/Application/NavigationConfig.h"

class ICONICCUBEGAME_API FMyGameNavigationConfig : public FNavigationConfig
{

public:
	FMyGameNavigationConfig();
	virtual EUINavigationAction GetNavigationActionForKey(const FKey& InKey) const;
};