// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCheckBoxStyle.h"

void FMyLeftCheckBoxStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	OutBrushes.Add(&CheckedImage);
	OutBrushes.Add(&UncheckedImage);
	OutBrushes.Add(&CheckedPressedImage);
	
	OutBrushes.Add(&NormalImage);
	OutBrushes.Add(&HoverImage);
	NormalTextStyle.GetResources(OutBrushes);
	HoverTextStyle.GetResources(OutBrushes);
}
const FName FMyLeftCheckBoxStyle::TypeName = TEXT("FMyCheckBoxStyle");
const FName FMyLeftCheckBoxStyle::GetTypeName() const
{
	static const FName TypeName = TEXT("FMyCheckBoxStyle");
	return FName();
}

const FMyLeftCheckBoxStyle & FMyLeftCheckBoxStyle::GetDefault()
{
	static FMyLeftCheckBoxStyle Default;
	return Default;
}
UMyCheckBoxStyle::UMyCheckBoxStyle(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}