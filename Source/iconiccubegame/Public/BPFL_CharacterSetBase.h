// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_CharacterSetBase.generated.h"

/**
 * 
 */
UCLASS()
class ICONICCUBEGAME_API UBPFL_CharacterSetBase : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable)
		static void CharacterSetBase(ACharacter* Character, UPrimitiveComponent* Primitive, bool Reset);
};
