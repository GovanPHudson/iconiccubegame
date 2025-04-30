// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IntToAscii.generated.h"

/**
 * 
 */
UCLASS()
class ICONICCUBEGAME_API UIntToAscii : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString IntToAscii(int number);
};
