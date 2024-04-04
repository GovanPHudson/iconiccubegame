// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ObjectMacros.h"
#include "CustomVertexPainting.generated.h"

class UStaticMeshComponent;

UCLASS()
class ICONICCUBEGAME_API UCustomVertexPainting : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "VertexPaint")
	static void PaintVerticesRadius(UStaticMeshComponent* StaticMeshComponent, const FLinearColor& StartColor, const FLinearColor& EndColor, float Radius = 1000, bool bConvertToSRGB = true);
	UFUNCTION(BlueprintCallable, Category = "VertexPaint")
	static void PaintVerticesRadiusOverlay(UStaticMeshComponent* StaticMeshComponent, const FLinearColor& StartColor, const FLinearColor& EndColor, float Radius = 1000, bool bConvertToSRGB = true);
	UFUNCTION(BlueprintCallable, Category = "VertexPaint")
	static void GetVertexColorForExport(UStaticMeshComponent* StaticMeshComponent, bool& Success, TArray<FString>& OutputArray);
	UFUNCTION(BlueprintCallable, Category = "VertexPaint")
	static void SetVertexColorFromExport(UStaticMeshComponent* StaticMeshComponent, TArray<FString> InputArray, bool& Success);


	static void ReadTextSafe(const TCHAR* SourceText, TArray<FColor>& OutputColorArray);
};



