// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class MYPROJECT1_API SMySAssetView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMySAssetView) 
		: _Content()
		, _HAlign(HAlign_Fill)
		, _VAlign(VAlign_Fill)
	{}
	SLATE_ARGUMENT(EHorizontalAlignment, HAlign)
	SLATE_ARGUMENT(EVerticalAlignment, VAlign)

	SLATE_DEFAULT_SLOT(FArguments, Content)
	SLATE_ARGUMENT(APlayerController*, MyPlayerController)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual void SetContent(TSharedRef< SWidget > InContent);

	/** See HAlign argument */
	void SetHAlign(EHorizontalAlignment HAlign);

	/** See VAlign argument */
	void SetVAlign(EVerticalAlignment VAlign);
public:
	virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;
protected:
	APlayerController* MyPlayerController;
};
