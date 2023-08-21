// Fill out your copyright notice in the Description page of Project Settings.


#include "MeasureTextLength.h"
#include "Rendering/SlateRenderer.h"
#include "Fonts/FontMeasure.h"

FVector2D UMeasureTextLength::MeasureStringGivenFont(const FString testString, const FSlateFontInfo testFont)
{
	TSharedRef<FSlateFontMeasure> FontMeasure = (FSlateApplication::Get().GetRenderer()->GetFontMeasureService());
	FVector2D testResult;
	
	testResult = FontMeasure->Measure(testString, testFont);

	return testResult;
}