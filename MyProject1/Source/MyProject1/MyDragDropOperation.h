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
	
	//ԭ����protect ���ڸĳ���public
	virtual void Construct() override;

	virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;

private:
	//����ͼ�Ĵ�С
	int ThumbnailSize;
};
