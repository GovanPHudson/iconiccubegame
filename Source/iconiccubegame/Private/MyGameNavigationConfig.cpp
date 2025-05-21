
#include "MyGameNavigationConfig.h"
#include "InputCoreTypes.h"

FMyGameNavigationConfig::FMyGameNavigationConfig()
{
    KeyEventRules.Reset();

	AnalogHorizontalKey = EKeys::Invalid;//OculusTouch_Left_Thumbstick_X;
	AnalogVerticalKey = EKeys::Invalid;//OculusTouch_Left_Thumbstick_Y;

	KeyEventRules.Emplace(EKeys::OculusTouch_Left_Thumbstick_Up		, EUINavigation::Up);
	KeyEventRules.Emplace(EKeys::OculusTouch_Left_Thumbstick_Down	, EUINavigation::Down);
	KeyEventRules.Emplace(EKeys::OculusTouch_Left_Thumbstick_Left	, EUINavigation::Left);
	KeyEventRules.Emplace(EKeys::OculusTouch_Left_Thumbstick_Right	, EUINavigation::Right);

}

EUINavigationAction FMyGameNavigationConfig::GetNavigationActionForKey(const FKey& InKey) const
{

	//UI Selection Key
	if (InKey == EKeys::OculusTouch_Left_Trigger_Click)
	{
		return EUINavigationAction::Accept;
	}
	//UI Back key
	else if ( InKey == EKeys::OculusTouch_Right_Trigger_Click)
	{
		return EUINavigationAction::Back;
	}

	return EUINavigationAction::Invalid;
}