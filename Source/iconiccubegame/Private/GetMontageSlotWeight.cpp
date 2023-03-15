// Fill out your copyright notice in the Description page of Project Settings.


#include "GetMontageSlotWeight.h"
#include "Animation/AnimInstance.h"

// ...other includes and code for other things...]

float UGetMontageSlotWeight::GetMontageSlotWeight(const UAnimInstance* Anim, const FName SlotName)
{
	float val = 0.0f;
	
	val = Anim->GetSlotMontageGlobalWeight(SlotName);

	return val;
}
	
	