// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MeasureTextLength.generated.h"

/**
 * 
 */
UCLASS()
class ICONICCUBEGAME_API UMeasureTextLength : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "String")
	static FVector2D MeasureStringGivenFont(const FString testString, const FSlateFontInfo testFont);
};
