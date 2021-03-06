// Fill out your copyright notice in the Description page of Project Settings.

#include "ProductWidgetUI.h"
#include "MyLeftMenuWidgetStyle.h"
#include "GameFramework/PlayerController.h"
#include "MyMenuStyle.h"
#include "MyWallPawn.h"
#include "Engine.h"
#include "CanDragWidget.h"

#define LOCTEXT_NAMESPACE "SProductWidgetUI"
BEGIN_FUNCTION_BUILD_OPTIMIZATION
void SProductWidgetUI::Construct(const FArguments & args)
{
	ProductStyle = &FMyMenuStyle::Get().GetWidgetStyle<FLeftMenuStyle>("LeftMenuStyle");
	ProductImage = args._ProductImage;
	IsCollected = args._IsCollected;
	MaterialID = args._MaterialID;
	MyPlayerController = args._MyPlayerController;
	/*ChangeMaterial = args._ChangeMaterial;
	Pawn = args._Pawn;*/
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(260)
		.HeightOverride(260)
		.Padding(FMargin(5))
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SBox)
					.HeightOverride(200)   //product image
					[      
						SNew(SOverlay)
						+SOverlay::Slot()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SNew(SImage)
							.Image(this, &SProductWidgetUI::GetProductImage)
						]
						+SOverlay::Slot()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SNew(SCanDragWidget)
							.MaterialID(MaterialID)
							.Cursor(EMouseCursor::GrabHand)
						]
						
					]
				]
				+SVerticalBox::Slot()  //product operation
				.AutoHeight()
				[
					SNew(SBox)
					.HeightOverride(50)
					[
						SNew(SOverlay)  //background Color
						+SOverlay::Slot()
						[
							SNew(SColorBlock)
							.Color(FLinearColor(0.026241f, 0.022174f, 0.019382f))
						]
						+SOverlay::Slot()
						[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()  // product description
							.AutoWidth()
							[
								SNew(SBox)
								.WidthOverride(140)
								[
									SNew(SVerticalBox)
									+SVerticalBox::Slot()
									.AutoHeight()
									[
										SNew(SBox)   //product name
										.HeightOverride(25)
										.VAlign(VAlign_Center)
										.Padding(FMargin(10,0,0,0))
										[
											SNew(STextBlock)
											.Font(FSlateFontInfo("宋体",10))
											.Text(LOCTEXT("PT11","实木地板"))
										]
									]
									+SVerticalBox::Slot()
									.AutoHeight()
									[
										SNew(SBox)   //product price
										.HeightOverride(25)
										.VAlign(VAlign_Center)
										.Padding(FMargin(10, 0, 0, 0))
										[
											SNew(STextBlock)
											.Font(FSlateFontInfo("宋体", 10))
											.Text(FText::FromString("$120"))
										]
									]
								]
							]
							+SHorizontalBox::Slot()
							.AutoWidth()  // logo
							[
								SNew(SBox)
								.WidthOverride(50)
								.Padding(FMargin(10,16,17,14))
								[
									SNew(SButton)
									.ButtonStyle(&ProductStyle->ProductLogoButtonStyle)
								]
							]
							+SHorizontalBox::Slot()
							.AutoWidth()
							[
								SNew(SBox)
								.WidthOverride(60)
								.Padding(FMargin(6,13))
								[
									SNew(SButton)
									.VAlign(VAlign_Center)
									.HAlign(HAlign_Center)
									.ButtonStyle(&ProductStyle->ProductApplyButtonStyle)
									.OnClicked(this,&SProductWidgetUI::GetChangeMaterial)
									[
										SNew(STextBlock)
										//.TextStyle(&ProductStyle->ProductApplyTextStyle)
										.Font(FSlateFontInfo("宋体", 10))
										.ColorAndOpacity(FLinearColor::White)
										.Text(LOCTEXT("Apply","应用"))
									]
								]
							]
						]
					]
				]
			]
			+SOverlay::Slot()
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SBox)
					.HeightOverride(80)
					[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						.HAlign(HAlign_Left)
						.AutoWidth()
						[
							SNew(SBox)
							.WidthOverride(50)
							.Padding(FMargin(5,20))
							[	
								SNew(SButton)
								.ButtonStyle(&ProductStyle->ProductCollectButtonStyle)
								.OnClicked(this,&SProductWidgetUI::SetProductIsCollected)
								.VAlign(VAlign_Center)
								.HAlign(HAlign_Center)
								// lack an Image  collect
								[
									
									
										SNew(SImage)
										.Image(this, &SProductWidgetUI::GetProductCollectImage)
									
									
								]
							]
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(SBox)
							.WidthOverride(200)
							[
								SNew(SHorizontalBox)
								+SHorizontalBox::Slot()
								.FillWidth(1.0f)
								.HAlign(HAlign_Right)
								[
									SNew(SBox)
									.WidthOverride(67)
									.Padding(FMargin(0,0,0,1))
									[
										SNew(SImage)
										.Image(&ProductStyle->ProductRecommendImage)
										
									]
								]
							]
						]
					]
				]
			]
		]

	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE
const FSlateBrush* SProductWidgetUI::GetProductImage() const
{
	return ProductImage;
}

FReply SProductWidgetUI::SetProductIsCollected()
{
	IsCollected = !IsCollected;
	return FReply::Handled();
}

const FSlateBrush* SProductWidgetUI::GetProductCollectImage() const
{
	if (IsCollected)
	{
		return &ProductStyle->ProductCollectedImage;
	}
	else
	{
		return &ProductStyle->ProductNoCollectImage;
	}
}

FReply SProductWidgetUI::GetChangeMaterial() const
{
	if (MyPlayerController)
	{
 		AMyWallPawn* MyPawn = Cast<AMyWallPawn>(MyPlayerController->GetPawn());
		if (MyPawn)
		{
			if (MaterialID==1)
			{
				
				MyPawn->MaterialID = MaterialID;
				//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("赋予蓝色"));
			}
			else
			{
				MyPawn->MaterialID = MaterialID;
				//MyPawn->ChangeMaterial = MyStaticMaterial::MyInitMaterial.OrangeMaterial.Get();
				//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("赋予黄色"));
			}
			
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("控制器存在"));
		}
		else {
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("玩家不存在"));
		}
		
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("控制器不存在"));
	}
	
	
	
	/*AMyWallPawn* MyPawn = Cast<AMyWallPawn>(Pawn);
	MyPawn->ChangeMaterial = ChangeMaterial;*/
	return FReply::Handled();
}
