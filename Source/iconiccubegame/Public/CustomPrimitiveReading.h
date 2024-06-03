// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/PrimitiveComponent.h"
#include "CustomPrimitiveReading.generated.h"


/**
 * 
 */
UCLASS()
class ICONICCUBEGAME_API UCustomPrimitiveReading : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Rendering")
	static void GetCustomPrimitiveDataBP(const UPrimitiveComponent *target, TArray<float>& Array);
	UFUNCTION(BlueprintCallable, Category = "Rendering")
	static void GetDefaultCustomPrimitiveDataBP(const UPrimitiveComponent *target, TArray<float>& Array);
};
