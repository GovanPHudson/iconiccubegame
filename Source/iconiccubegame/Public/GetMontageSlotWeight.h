// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GetMontageSlotWeight.generated.h"

/**
 * 
 */
UCLASS()
class ICONICCUBEGAME_API UGetMontageSlotWeight : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Montage")
	static float GetMontageSlotWeight(const UAnimInstance* Anim, const FName SlotName);
};
