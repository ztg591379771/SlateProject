// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"
#include "Materials/MaterialInstance.h"
/**
 *  
 */
class MYPROJECT1_API SProductWidgetUI : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SProductWidgetUI)
	{}
	SLATE_ARGUMENT(const FSlateBrush*, ProductImage)
	SLATE_ARGUMENT(bool,IsCollected)
	SLATE_ARGUMENT(int, MaterialID)
	SLATE_ARGUMENT(APlayerController*, MyPlayerController)
	/*SLATE_ARGUMENT(UMaterialInstance*,ChangeMaterial)
	SLATE_ARGUMENT(APawn*,Pawn)*/
	SLATE_END_ARGS()
	void Construct(const FArguments& args);

protected:
	//
	const FSlateBrush* ProductImage;
	bool IsCollected;
	int MaterialID;
	/* UMaterialInstance* ChangeMaterial;
	 APawn* Pawn;*/
	APlayerController* MyPlayerController;
private:
	// get ProductImage
	const FSlateBrush* GetProductImage() const;
	/*
	Create a product Style
	*/
	const struct FLeftMenuStyle* ProductStyle;

	/*
		set product collect or not
	*/
	FReply SetProductIsCollected();
	/*
		get product collect image
	*/
	const FSlateBrush* GetProductCollectImage() const;

    FReply GetChangeMaterial() const;
};
