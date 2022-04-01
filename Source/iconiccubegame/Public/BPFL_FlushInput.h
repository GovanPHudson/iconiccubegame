// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_FlushInput.generated.h"

/**
 * 
 */
UCLASS()
class ICONICCUBEGAME_API UBPFL_FlushInput : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable)
	static void flushInputs(const APlayerController* PlayerController);
};

