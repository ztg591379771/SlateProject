// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *   the Style set which can load our style and reference our style 
 */
class MYPROJECT1_API FMyMenuStyle
{
public:
	//  register our style 
	static void Initialize();

	// reset our style
	static void Shutdowm();

	//reload textures used by slate renderer 
	static void ReloadTextures();

	// get a SlateStyle
	static const class ISlateStyle& Get();

	//get the name of Style
	static FName GetStyleSetName();

private:
	//create the FSlateStyleSet
	static TSharedRef<class FSlateStyleSet> Create();

	//Singleton instance used for our Style Set
	static TSharedPtr<class FSlateStyleSet> MyMenuStyleInstance;
};
