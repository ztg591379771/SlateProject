// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCheckBoxUI.h"

void SMyCheckBoxUI::Construct(const FArguments& InArgs)
{
	//LeftCheckBoxStyle = &FMyMenuStyle::Get().GetWidgetStyle<FMyLeftCheckBoxStyle>("MyCheckBoxStyle");
	TArray<MyInfo> Categories;
	MyInfo Info1 = MyInfo(FText::FromString("Tool1"), FName("Apple1"));
	MyInfo Info2 = MyInfo(FText::FromString("Tool2"), FName("Apple2"));
	Categories.Add(Info1);
	Categories.Add(Info2);
	ActiveTabName = Categories.GetData()->UniqueHandle;
	bNeedsUpdate = true;
	MapInfo.Add(FName("Apple1"), Info1);
	MapInfo.Add(FName("Apple2"), Info2);
	TSharedRef<SVerticalBox> MyTaps = SNew(SVerticalBox);
	for (int index=0;index!=Categories.Num();index++)
	{
		MyTaps->AddSlot()
			.AutoHeight()
			[
				CreateMyInfoTap(Categories[index])
			];
	}
	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			MyTaps
		];

}

TSharedRef<SWidget> SMyCheckBoxUI::CreateMyInfoTap(const MyInfo & Info)
{
	return SNew(SCheckBox)
		.Style(&FMyMenuStyle::Get().GetWidgetStyle<FCheckBoxStyle>("CheckBoxStyle"))
		.OnCheckStateChanged(this, &SMyCheckBoxUI::OnPlacementTabChanged, Info.UniqueHandle)
		.IsChecked(this, &SMyCheckBoxUI::GetPlacementTabCheckedState, Info.UniqueHandle)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.VAlign(VAlign_Center)
			[
				SNew(SBox)
				.HeightOverride(50)
				[
					SNew(SOverlay)
					+SOverlay::Slot()
					[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(SBox)
							.WidthOverride(50)
							.Padding(FMargin(10,5,0,5))
							[
								SNew(SImage)
								.Image(FMyMenuStyle::Get().GetBrush("DiBan"))
							]
						]
						+SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(SBox)
							.WidthOverride(100)
							.VAlign(VAlign_Center)
							.Padding(FMargin(10,0,0,0))
							[
								SNew(STextBlock)
								.Font(FSlateFontInfo("微软雅黑",14))
								//.TextStyle(&LeftCheckBoxStyle->NormalTextStyle)
								.ColorAndOpacity(FLinearColor::Black)
								.Text(Info.DisPlayName)
							]
						]
					]
					
				]
			]
		/*	+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Left)
			[
				SNew(SBorder)
				.BorderImage(this, &SMyCheckBoxUI::PlacementGroupBorderImage, Info.UniqueHandle)

			]*/


		];



}

void SMyCheckBoxUI::OnPlacementTabChanged(ECheckBoxState NewState, FName CategoryName)
{
	if (NewState == ECheckBoxState::Checked)
	{
		ActiveTabName = CategoryName;
		//添加什么东西
		//IPlacementModeModule::Get().RegenerateItemsForCategory(ActiveTabName);

		bNeedsUpdate = true;
	}
}

ECheckBoxState SMyCheckBoxUI::GetPlacementTabCheckedState(FName CategoryName) const
{
	return ActiveTabName == CategoryName ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

const FSlateBrush * SMyCheckBoxUI::PlacementGroupBorderImage(FName CategoryName) const
{
	if (CategoryName == ActiveTabName)
	{
		return FMyMenuStyle::Get().GetBrush("Red"); //当选中时一种图片，暂时先不妨图片
	}
	else
	{
		return nullptr;
	}
}

FText SMyCheckBoxUI::GetDynamicText() const
{
	return FText();
}
