// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/DragAndDrop.h"

/**
 * 
 */
class MYPROJECT1_API FMyDragDropOperation : public FDragDropOperation
{
public:
	DRAG_DROP_OPERATOR_TYPE(FMyDragDropOperation, FDragDropOperation)
	int AssetData;
	static TSharedRef<FMyDragDropOperation> New(const int InAssetDate);
	
	//原来是protect 现在改成了public
	virtual void Construct() override;

	virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;

private:
	//缩略图的大小
	int ThumbnailSize;
};
