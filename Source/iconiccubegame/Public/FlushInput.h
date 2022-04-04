// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FlushInput.generated.h"

/**
 * 
 */
UCLASS()
class ICONICCUBEGAME_API UFlushInput : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Input")
	static void flushInputs(const APlayerController* PlayerController);
};
