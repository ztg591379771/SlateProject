// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGlobalMenuUI.h"
#include "MyGlobalStyle.h"
#include "MyMenuStyle.h"
#include "MySComboButton.h"
#include "ProductWidgetUI.h"
#include "MyButton.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/Input/SSearchBox.h"
#include "Materials/MaterialInstance.h"
#include "Engine/Engine.h"
#include "MyCheckBoxUI.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h" 
#include "MySAssetView.h"
#define LOCTEXT_NAMESPACE "SMyGlobalMenuUI"


BEGIN_FUNCTION_BUILD_OPTIMIZATION
//8.
void SMyGlobalMenuUI::Construct(const FArguments& args)
{

	//9.
	OwnerHUD = args._OwnerHUD;
	MenuStyle = &FMyMenuStyle::Get().GetWidgetStyle<FMyGlobalStyle>("MyGlobalStyle");
	LeftMenuStyle = &FMyMenuStyle::Get().GetWidgetStyle<FLeftMenuStyle>("LeftMenuStyle");
	LeftMenuVisiblility = EVisibility::Hidden;
	LittleLeftMenuVisiblility = EVisibility::Hidden;
	
	TSharedRef<SMySComboButton> S1 = SNew(SMySComboButton);
	

	TSharedRef< SVerticalBox > productSVBox=SNew(SVerticalBox);
	
	for (int i=0;i<5;i++)
	{
		productSVBox->AddSlot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SProductWidgetUI)
				.ProductImage(&LeftMenuStyle->ProductImage)
				.IsCollected(true)
				.MaterialID(0)
				.MyPlayerController(OwnerHUD->getMyController())
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SProductWidgetUI)
				.ProductImage(FMyMenuStyle::Get().GetBrush("productImage"))
				.IsCollected(false)
				.MaterialID(1)
				.MyPlayerController(OwnerHUD->getMyController())
			]
		];
	}



	ChildSlot
	[
		SNew(SMySAssetView)
		.MyPlayerController(OwnerHUD->getMyController())
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Fill)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
			SNew(SBorder)
			.BorderBackgroundColor(FLinearColor::White)
			.Padding(FMargin(0))
			[
				SNew(SBox)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Top)
				.HeightOverride(100)
				[
					SNew(SOverlay)
					+SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SImage)
						.Image(FMyMenuStyle::Get().GetBrush("BackGroud"))
					]
					+SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SHorizontalBox)
						//logo
						+SHorizontalBox::Slot() 
						.AutoWidth()
						[
							SNew(SVerticalBox)
							+SVerticalBox::Slot()
							.HAlign(HAlign_Left)
							.Padding(FMargin(30,15))
							[
								SNew(SBox)
								.WidthOverride(400)
								.HeightOverride(80)
								[
									SNew(SImage)
									.Image(&MenuStyle->LogoImage)
								]
							]
					
						]
						// button  Shopping
						+SHorizontalBox::Slot()
						.HAlign(HAlign_Left)
						.AutoWidth()
						[
							SNew(SMySComboButton)
							.DefaultImage(FMyMenuStyle::Get().GetBrush("DeFaultShoppingIcon"))
							.HoveredImage(FMyMenuStyle::Get().GetBrush("HoveredShoppingIcon"))
							
							.ButtonContent()
							[
								SNew(STextBlock)
								.TextStyle(&MenuStyle->MyComBoTextStyle)
			
								.Text(LOCTEXT("shopping","家具商城"))
							]
							.MenuContent()
							[
								SNew(SVerticalBox)
								+SVerticalBox::Slot()
								
								.AutoHeight()
								[
									SNew(SBox)
									.HeightOverride(45)
									.HAlign(HAlign_Fill)
									
									[
										SNew(SButton)
										.ButtonStyle(&MenuStyle->MyComboContentButtonStyle)
										.OnClicked(this,&SMyGlobalMenuUI::SetLeftMenuVisible)
										
										.TextStyle(&MenuStyle->MyComboContentTextStyle)
										.Text(LOCTEXT("decorate", "家居装饰"))
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										/*[
											SNew(STextBlock)
											.TextStyle(&MenuStyle->MyComboContentTextStyle)
											.Text(LOCTEXT("decorate", "家居装饰"))
										]*/
									]
								]
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									SNew(SBox)
									.HeightOverride(45)
									.HAlign(HAlign_Fill)
									[
										SNew(SButton)
										.ButtonStyle(&MenuStyle->MyComboContentButtonStyle)
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										[
											SNew(STextBlock)
											.TextStyle(&MenuStyle->MyComboContentTextStyle)
											.Text(LOCTEXT("Goods", "生活用品"))
										]
									]
								]
							]
					
						]
						// button  Save
						+ SHorizontalBox::Slot()
						.HAlign(HAlign_Left)
						.AutoWidth()
						[
							SNew(SMySComboButton)
							.DefaultImage(FMyMenuStyle::Get().GetBrush("DeFaultSaveIcon"))
							.HoveredImage(FMyMenuStyle::Get().GetBrush("HoveredSavelIcon"))
							.ButtonContent()
							[
								SNew(STextBlock)
								.TextStyle(&MenuStyle->MyComBoTextStyle)
								.Text(LOCTEXT("Save", "保存方案"))
							]
							.MenuContent()
							[
								SNew(SVerticalBox)
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									SNew(SBox)
									.HeightOverride(45)
									.HAlign(HAlign_Fill)
									[
										SNew(SButton)
										.ButtonStyle(&MenuStyle->MyComboContentButtonStyle)
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										[
											SNew(STextBlock)
											.TextStyle(&MenuStyle->MyComboContentTextStyle)
											.Text(LOCTEXT("only Save", "仅保存"))
										]	
									]
								]
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									SNew(SBox)
									.HeightOverride(45)
									.HAlign(HAlign_Fill)
									[
										SNew(SButton)
										.ButtonStyle(&MenuStyle->MyComboContentButtonStyle)
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										[
											SNew(STextBlock)
											.TextStyle(&MenuStyle->MyComboContentTextStyle)
											.Text(LOCTEXT("Save Other", "另存为"))
										]
									]
								]
							]

						]
						// button  Save
						+ SHorizontalBox::Slot()
						.HAlign(HAlign_Left)
						.AutoWidth()
						[
							SNew(SMySComboButton)
							.DefaultImage(FMyMenuStyle::Get().GetBrush("DeFaultToolIcon"))
							.HoveredImage(FMyMenuStyle::Get().GetBrush("HoveredToolIcon"))
							.ButtonContent()
							[
								SNew(STextBlock)
								.TextStyle(&MenuStyle->MyComBoTextStyle)
								.Text(LOCTEXT("Tools", "工具"))
							]
							.MenuContent()
							[
								SNew(SVerticalBox)
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									SNew(SBox)
									.HeightOverride(45)
									.HAlign(HAlign_Fill)
									[
										SNew(SButton)
										.ButtonStyle(&MenuStyle->MyComboContentButtonStyle)
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										[
											SNew(STextBlock)
											.TextStyle(&MenuStyle->MyComboContentTextStyle)
											.Text(LOCTEXT("Import", "导出"))
										]
									]
								]
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									SNew(SBox)
									.HeightOverride(45)
									.HAlign(HAlign_Fill)
									[
										SNew(SButton)
										.ButtonStyle(&MenuStyle->MyComboContentButtonStyle)
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										[
											SNew(STextBlock)
											.TextStyle(&MenuStyle->MyComboContentTextStyle)
											.Text(LOCTEXT("Er Wei Ma", "生成二维码"))
										]
									]
								]
							]

						]
						// right message
						+ SHorizontalBox::Slot()
						.HAlign(HAlign_Fill)
						.FillWidth(1)
						[
							SNew(SOverlay)
							+SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								SNew(SHorizontalBox)
								+ SHorizontalBox::Slot()
								.HAlign(HAlign_Right)
								[
									SNew(SHorizontalBox)  
									+ SHorizontalBox::Slot() //  Personal Center
									.AutoWidth()
									[
										SNew(SBox)
										.WidthOverride(100)
										.Padding(FMargin(15))
										[
											SNew(SComboButton)
											.HAlign(HAlign_Fill)
											.VAlign(VAlign_Fill)
											.ButtonStyle(&MenuStyle->PersonalButtonStyle)
											.ContentPadding(FMargin(0))
											.HasDownArrow(false)
											.ButtonContent()
											[
												SNew(SImage)
												.Image(&MenuStyle->PersonalImage)
											]
											.MenuContent()
											[
												SNew(SVerticalBox)
												+ SVerticalBox::Slot()
												.AutoHeight()
												[
													SNew(SBox)
													.HeightOverride(45)
													.HAlign(HAlign_Fill)
													[
														SNew(SButton)
														.ButtonStyle(&MenuStyle->MyComboContentButtonStyle)
														.HAlign(HAlign_Center)
														.VAlign(VAlign_Center)
														[
															SNew(STextBlock)
															.TextStyle(&MenuStyle->MyComboContentTextStyle)
															.Text(LOCTEXT("update password", "修改密码"))
														]
													]
												]
												+ SVerticalBox::Slot()
												.AutoHeight()
												[
													SNew(SBox)
													.HeightOverride(45)
													.HAlign(HAlign_Fill)
													[
														SNew(SButton)
														.ButtonStyle(&MenuStyle->MyComboContentButtonStyle)
														.HAlign(HAlign_Center)
														.VAlign(VAlign_Center)
														[
															SNew(STextBlock)
															.TextStyle(&MenuStyle->MyComboContentTextStyle)
															.Text(LOCTEXT("update massage", "修改个人信息"))
														]
													]
												]
											]

										]
									]
									+SHorizontalBox::Slot() // version
									.AutoWidth()
									[
										SNew(SVerticalBox)
										+ SVerticalBox::Slot()
										.AutoHeight()
										[
											SNew(SBox)
											.WidthOverride(100)
											.HeightOverride(50)
											.VAlign(VAlign_Fill)
											[
												SNew(SBox)
												.Padding(FMargin(10,16,20,5))
												[
													SNew(SOverlay)
													+SOverlay::Slot()
													.HAlign(HAlign_Fill)
													[
														SNew(SColorBlock)
														.Color(FLinearColor(0.3564f, 0.005182f, 0.017642f))
													]
													+SOverlay::Slot()
													.VAlign(VAlign_Center)
													[
														SNew(STextBlock)
														.Font(FSlateFontInfo("宋体",16))
														.ColorAndOpacity(FLinearColor::White)
														.Text(LOCTEXT("Versions", "个人版"))
													]

												]
											]
										]
										+ SVerticalBox::Slot()
										.AutoHeight()
										[
											SNew(SBox)
											.WidthOverride(100)
											.HeightOverride(50)
											.VAlign(VAlign_Bottom)
											.Padding(FMargin(5,0,10,15))
											[
												//Dynamic access to data.
												SNew(STextBlock)
												.TextStyle(&MenuStyle->UserNameTextStyle)
												.Text(LOCTEXT("Welcome", "欢迎您!"))
											]
										]
								
									]
									+SHorizontalBox::Slot() // message
									.AutoWidth()
									[
										SNew(SVerticalBox)
										+ SVerticalBox::Slot()
										.AutoHeight()
										[
											SNew(SBox)
											.WidthOverride(100)
											.HeightOverride(50)
											[
												SNew(SHorizontalBox)
												+ SHorizontalBox::Slot()
												[
													SNew(SBox)
													.WidthOverride(25)
													.HeightOverride(25)
													.Padding(FMargin(12, 13))
													[
														SNew(SBox)
														.HAlign(HAlign_Fill)
														.VAlign(VAlign_Fill)
														[
															SNew(SButton)
															.ButtonStyle(&MenuStyle->ClothesButtonStyle)
														]
													]
												]
												+ SHorizontalBox::Slot()
												[
													SNew(SBox)
													.WidthOverride(25)
													.HeightOverride(25)	
													.Padding(FMargin(10,15))
													[
														SNew(SBox)
														.HAlign(HAlign_Fill)
														.VAlign(VAlign_Fill)
														[
															SNew(SButton)
															.ButtonStyle(&MenuStyle->EmailButtonStyle)
														]
													]

												]
											]
										]
										+ SVerticalBox::Slot()
										.AutoHeight()
										[
											SNew(SBox)
											.WidthOverride(100)
											.HeightOverride(50)
											.VAlign(VAlign_Bottom)
											.Padding(FMargin(0, 0, 10, 15))
											[
												//Dynamic access to data.
												SNew(STextBlock)
												.TextStyle(&MenuStyle->UserNameTextStyle)
												.Text(this,&SMyGlobalMenuUI::GetUserName)
											]
										]
								
									]
									+ SHorizontalBox::Slot()  //four buttons
									.AutoWidth()
									[
										SNew(SBox)
										.WidthOverride(150)
										.Padding(FMargin(0,30,30,30))
										[
											SNew(SMyButton)
											.ButtonStyle(&MenuStyle->RightFourButtonStyle)
											.Text(LOCTEXT("buy", "充值续费"))
											.HAlign(HAlign_Center)
											.VAlign(VAlign_Center)
											
										]
									]
									+ SHorizontalBox::Slot()
									.AutoWidth()
									[
										SNew(SBox)
										.WidthOverride(150)
										.Padding(FMargin(0, 30, 30, 30))
										[
											SNew(SMyButton)
											.ButtonStyle(&MenuStyle->RightFourButtonStyle)
											.Text(LOCTEXT("help", "帮  助"))
											.HAlign(HAlign_Center)
											.VAlign(VAlign_Center)
											
										]
									]
									+ SHorizontalBox::Slot()
									.AutoWidth()
									[
										SNew(SBox)
										.WidthOverride(150)
										.Padding(FMargin(0, 30, 30, 30))
										[
											SNew(SMyButton)
											.ButtonStyle(&MenuStyle->RightFourButtonStyle)
											.Text(LOCTEXT("comeback", "返  回"))
											.HAlign(HAlign_Center)
											.VAlign(VAlign_Center)
											
										]
									]
									+ SHorizontalBox::Slot()
									.AutoWidth()
									[
										SNew(SBox)
										.WidthOverride(150)
										.Padding(FMargin(0, 30, 30, 30))
										[
											SNew(SMyButton)
											.ButtonStyle(&MenuStyle->RightFourButtonStyle)
											.Text(LOCTEXT("out", "退出登陆"))
											.OnClicked(this,&SMyGlobalMenuUI::QuitMyGame)
											.HAlign(HAlign_Center)
											.VAlign(VAlign_Center)
											
										]
									]//four buttons
	
								]
							

						

							]
						
						]
					]
				]
			]
		]
		//Left
		+SVerticalBox::Slot()
		.HAlign(HAlign_Left)
		.FillHeight(1.0)
		[
			SNew(SBox)
			.HeightOverride(1080)
			.WidthOverride(700)
			[
			
			
			SNew(SOverlay)
			+SOverlay::Slot()
			[
				SNew(SHorizontalBox)
				.Visibility(this, &SMyGlobalMenuUI::GetLeftMenuVisibility)
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
						SNew(SBox)
						.HeightOverride(1080)
						.WidthOverride(700)
						[
							SNew(SOverlay)
							+SOverlay::Slot()
							[
								SNew(SImage)
								/*.Color(FLinearColor(0.73791f, 0.73791f, 0.814847f))*/
								.Image(FMyMenuStyle::Get().GetBrush("BackGroud"))
							]
							+SOverlay::Slot()
							[
								SNew(SHorizontalBox)
								+SHorizontalBox::Slot()
								.AutoWidth()
								[
										SNew(SBox)   //Left Menu
										.WidthOverride(150)
										[
											SNew(SVerticalBox)
											+SVerticalBox::Slot()
											.AutoHeight()
											[
												
													SNew(SBox)
													.HeightOverride(65)
													[
														SNew(SHorizontalBox)
														+SHorizontalBox::Slot()
														.AutoWidth()
														[
															SNew(SBox)
															.WidthOverride(110)
															
															[
																SNew(SOverlay)
																+SOverlay::Slot()
																[
																	SNew(SColorBlock)
																	.Color(FLinearColor(0.3564f, 0.005182f, 0.017642f))
																]
																+SOverlay::Slot()
																[
																	SNew(SBox)
																	.VAlign(VAlign_Center)
																	.HAlign(HAlign_Center)
																	[
																		SNew(STextBlock)
																		.ColorAndOpacity(FLinearColor::White)
																		.Font(FSlateFontInfo("微软雅黑",16))
																		.Text(LOCTEXT("Menu", "家装主材"))
																	]
																	
																]
																
															]
														]
														+ SHorizontalBox::Slot()
														.AutoWidth()
														[
															SNew(SBox)
															.WidthOverride(40)
															[
																SNew(SButton)
																.ButtonStyle(&LeftMenuStyle->DisplayButtonStyle)
																.OnClicked(this,&SMyGlobalMenuUI::SetLittleLeftMenuVisible)
																[
																	SNew(SBox)
																	.Padding(FMargin(2,12))
																	[
																		SNew(SImage)
																		.Image(&LeftMenuStyle->DisplayLeftImage)
																	]
																]
															]
														]
													]
												//]
											]
											+ SVerticalBox::Slot()   // left shopping 
											.AutoHeight() 
											[
												SNew(SMyCheckBoxUI)
												
											]
										]
									
								
								]
								//Right shopping
								+SHorizontalBox::Slot()
								.AutoWidth()
								[
									SNew(SBorder)
									.BorderBackgroundColor(FLinearColor::White)
									.Padding(FMargin(0))
									[
										SNew(SBox)
										.WidthOverride(550)
										[
											SNew(SOverlay)
											+SOverlay::Slot()
											[
												SNew(SColorBlock)
												.Color(FLinearColor(1.0f,1.0f,1.0f))
											]
											+SOverlay::Slot()
											[
												SNew(SVerticalBox)
												+SVerticalBox::Slot()
												.AutoHeight()
												[             //1.
													SNew(SBox)
													.HeightOverride(100)
													.Padding(FMargin(0,15))
													[
														SNew(SVerticalBox)
														+SVerticalBox::Slot()
														.AutoHeight()
														[
															SNew(SBox)
															.HeightOverride(35)
															[
																SNew(SHorizontalBox)
																+SHorizontalBox::Slot()
																.AutoWidth()
																[
																	SNew(SBox)
																	.Padding(FMargin(10,0,0,0))
																	.VAlign(VAlign_Center)
																	.WidthOverride(60)
																	[
																		SNew(STextBlock)
																		.TextStyle(&LeftMenuStyle->ClassTextStyle)
																		.Text(LOCTEXT("class","分类"))
																	]
																]
																+SHorizontalBox::Slot()
																.AutoWidth()
																.Padding(FMargin(0,3))
																[
																	SNew(SOverlay)
																	+SOverlay::Slot()
																	.HAlign(HAlign_Left)
																	.VAlign(VAlign_Fill)
																	[
																		SNew(SBorder)
																		.BorderBackgroundColor(FLinearColor::Black)
																	]
																	+SOverlay::Slot()
																	[
																		SNew(SHorizontalBox)
																		+SHorizontalBox::Slot()
																		.AutoWidth()
																		[
																			SNew(SBox)
																			.Padding(FMargin(5, 0, 0, 0))
																			.VAlign(VAlign_Center)
																			[
																				SNew(SButton)
																				.ButtonStyle(&LeftMenuStyle->ClassButtonStyle)
																				.VAlign(VAlign_Center)
																				[
																					SNew(STextBlock)
																					.TextStyle(&LeftMenuStyle->ClassButtonContentTextStyle)
																					.Text(LOCTEXT("BMW","宝马"))
																				]
																			]
																		]
																		+SHorizontalBox::Slot()
																		.AutoWidth()
																		[
																	
																			SNew(SBox)
																			.Padding(FMargin(5, 0, 0, 0))
																			.VAlign(VAlign_Center)
																			[
																				SNew(SButton)
																				.ButtonStyle(&LeftMenuStyle->ClassButtonStyle)
																				.VAlign(VAlign_Center)
																				[
																					SNew(STextBlock)
																					.TextStyle(&LeftMenuStyle->ClassButtonContentTextStyle)
																					.Text(LOCTEXT("OO","奥迪"))
																				]
																			]
																		]
																	]
																	
																]
																
															]
															
														]
														+SVerticalBox::Slot()
														.AutoHeight()
														[
															SNew(SBox)
															.HeightOverride(35)
															[
																SNew(SHorizontalBox)
																+SHorizontalBox::Slot()
																.AutoWidth()
																[
																	SNew(SBox)
																	.Padding(FMargin(10,0,0,0))
																	.VAlign(VAlign_Center)
																	.WidthOverride(60)
																	[
																		SNew(STextBlock)
																		.TextStyle(&LeftMenuStyle->ClassTextStyle)
																		.Text(LOCTEXT("brand","品牌"))
																	]
																]
																+SHorizontalBox::Slot()
																.Padding(FMargin(0,3))
																.AutoWidth()
																[
																	SNew(SOverlay)
																	+SOverlay::Slot()
																	.HAlign(HAlign_Left)
																	.VAlign(VAlign_Fill)
																	[
																		SNew(SBorder)
																		.BorderBackgroundColor(FLinearColor::Black)
																	]
																	+SOverlay::Slot()
																	[
																		SNew(SHorizontalBox)
																		+SHorizontalBox::Slot()
																		.AutoWidth()
																		[
																			SNew(SBox)
																			.Padding(FMargin(5, 0, 0, 0))
																			.VAlign(VAlign_Center)
																			[
																				SNew(SButton)
																				.ButtonStyle(&LeftMenuStyle->ClassButtonStyle)
																				.VAlign(VAlign_Center)
																				[
																					SNew(STextBlock)
																					.TextStyle(&LeftMenuStyle->ClassButtonContentTextStyle)
																					.Text(LOCTEXT("1","四轮"))
																				]
																			]
																		]
																		+SHorizontalBox::Slot()
																		.AutoWidth()
																		[
																			SNew(SBox)
																			.Padding(FMargin(5, 0, 0, 0))
																			.VAlign(VAlign_Center)
																			[
																				SNew(SButton)
																				.ButtonStyle(&LeftMenuStyle->ClassButtonStyle)
																				.VAlign(VAlign_Center)
																				[
																					SNew(STextBlock)
																					.TextStyle(&LeftMenuStyle->ClassButtonContentTextStyle)
																					.Text(LOCTEXT("2","三轮"))
																				]
																			]
																		]
																		
																	]
																]
															]
															
														]
													]
												]
												+SVerticalBox::Slot()
												.AutoHeight()
												[                 //2 search block
													SNew(SBox)
													.HeightOverride(40)
													.Padding(FMargin(10,0,30,10))
													[
														SNew(SSearchBox)
														.HintText(LOCTEXT("search","查询  | 车"))
														
														.OnTextChanged(this, &SMyGlobalMenuUI::OnSearchChanged)
														.OnTextCommitted(this, &SMyGlobalMenuUI::OnSearchCommitted)
													]
												]
												+SVerticalBox::Slot()
												.AutoHeight()
												[              //3 Shopping display
													SNew(SBox)
													.HeightOverride(780)
													
													[
														SNew(SScrollBox)
														+ SScrollBox::Slot()
														.Padding(5)
														[
															productSVBox
														]

													//	SNew(SHorizontalBox)
													//	+SHorizontalBox::Slot()
													//	.AutoWidth()
													//	[
													//		SNew(SBox)
													//		.WidthOverride(520)
													//		[
													//			
													//			//SNew(SColorBlock)
													//			//.Color(FLinearColor(1.0f, 1.0f, 1.0f))
													//			//SAssignNew(productSVBox,SVerticalBox)
													//			productSVBox
													//			
													//			
													//			
													//		]
													//	]
													//	+SHorizontalBox::Slot()
													//	.AutoWidth()
													//	[
													//		SNew(SBox)
													//		.WidthOverride(30)
													//		//.Padding(FMargin(5))
													//		[
													//			SNew(SScrollBar).Thickness(FVector2D(5, 5))
													//			//.OnUserScrolled(&SMyGlobalMenuUI::ScrollBar_OnUserScrolled)
													//			//SNew(SColorBlock)
													//			//.Color(FLinearColor(0.3f, 0.3f, 0.0f))
													//		]
													//	]

													]
												]
												+SVerticalBox::Slot()
												.AutoHeight()
												[              //4
													SNew(SBox)
													.HeightOverride(60)
													[
														SNew(SOverlay)
														/*+SOverlay::Slot()
														[
															SNew(SColorBlock)
															.Color(FLinearColor(0.0f, 0.0f, 0f))
														]*/
														+SOverlay::Slot()
														.HAlign(HAlign_Fill)
														.VAlign(VAlign_Fill)
														[
															SNew(SVerticalBox)
															+SVerticalBox::Slot()
															.VAlign(VAlign_Center)
															.HAlign(HAlign_Center)
															[
																SNew(SHorizontalBox)
																+SHorizontalBox::Slot()
																/*.Padding(FMargin(0,15))*/
																.HAlign(HAlign_Center)
																[
																	SNew(SBox)
																	.WidthOverride(70)
																	.Padding(FMargin(5,15))
																	[
																		SNew(SButton)
																		.ButtonStyle(&FMyMenuStyle::Get().GetWidgetStyle<FButtonStyle>("FanYe"))
																		.HAlign(HAlign_Center)
																		.VAlign(VAlign_Center)
																		[
																			SNew(STextBlock)
																			.Font(FSlateFontInfo("宋体", 12))
																			.ColorAndOpacity(FLinearColor::Black)
																			.Text(LOCTEXT("pre", "上一页"))
																		]

																	]
																]
																+SHorizontalBox::Slot()
																/*.Padding(FMargin(0,15))*/
																.HAlign(HAlign_Center)
																[
																	SNew(SBox)
																	.WidthOverride(70)
																	.Padding(FMargin(5,15))
																	.VAlign(VAlign_Center)
																	.HAlign(HAlign_Center)
																	[
																		SNew(STextBlock)
																		.Font(FSlateFontInfo("宋体",12))
																		.ColorAndOpacity(FLinearColor::Black)
																		.Text(LOCTEXT("fenye","1/10"))
																	]
																]
																+SHorizontalBox::Slot()
																/*.Padding(FMargin(0,15))*/
																.HAlign(HAlign_Center)
																[
																	SNew(SBox)
																	.WidthOverride(70)
																	.Padding(FMargin(5,15))
																	[
																		SNew(SButton)
																		.ButtonStyle(&FMyMenuStyle::Get().GetWidgetStyle<FButtonStyle>("FanYe"))
																		.HAlign(HAlign_Center)
																		.VAlign(VAlign_Center)
																		[
																			SNew(STextBlock)
																			.Font(FSlateFontInfo("宋体", 12))
																			.ColorAndOpacity(FLinearColor::Black)
																			.Text(LOCTEXT("past", "下一页"))
																		]

																	]
																]
																+SHorizontalBox::Slot()
																/*.Padding(FMargin(0,15))*/
																.HAlign(HAlign_Center)
																[
																	SNew(SBox)
																	.WidthOverride(70)
																	.Padding(FMargin(5,15))
																	[
																		SNew(SBorder)
																		.BorderBackgroundColor(FLinearColor::Black)
																		
																		[
																			SNew(SEditableTextBox)
																			
																		]
																		

																	]
																]
																+SHorizontalBox::Slot()
																/*.Padding(FMargin(0,15))*/
																.HAlign(HAlign_Center)
																[
																	SNew(SBox)
																	.WidthOverride(60)
																	.Padding(FMargin(5,15))
																	[
																		SNew(SButton)
																		.HAlign(HAlign_Center)
																		//.ButtonStyle(&FMyMenuStyle::Get().GetWidgetStyle<FButtonStyle>("FanYe"))
																		.VAlign(VAlign_Center)
																		[
																			SNew(STextBlock)
																			.Font(FSlateFontInfo("宋体", 12))
																			.ColorAndOpacity(FLinearColor::Black)
																			.Text(LOCTEXT("jump", "跳转"))
																		]

																	]
																]
																
															]
															
														]
														
													]
												]

											]
										]

									]
								]
							]
							
						]
					//]
					
					
				] 

			]
			+SOverlay::Slot() //little left menu
			[
				SNew(SHorizontalBox)
				.Visibility(this, &SMyGlobalMenuUI::GetLittleLeftMenuVisibility)
				+SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Fill)
				[
					SNew(SBorder)
					.BorderBackgroundColor(FLinearColor::White)
					.Padding(FMargin(0))
					[
						SNew(SBox)
						.HeightOverride(1080)
						.WidthOverride(80)
						[
							SNew(SVerticalBox)
							+SVerticalBox::Slot()
							.AutoHeight()
							[
								SNew(SBox)
								.HeightOverride(50)
								[
									SNew(SButton)
									.ButtonStyle(&LeftMenuStyle->DisplayButtonStyle)
									.OnClicked(this,&SMyGlobalMenuUI::SetLittleLeftMenuHidden)
									[
										SNew(SBox)
										.Padding(FMargin(22,7))
										[
											SNew(SImage)
											.Image(&LeftMenuStyle->DisplayRightImage)
										]
										
									]
								]
							]
							+SVerticalBox::Slot()
							.AutoHeight()
							[
								SNew(SBox)
								.HeightOverride(40)
								[
									SNew(SButton)
									.ButtonStyle(&LeftMenuStyle->ShoppingLittleLogoButtonStyle)
									[
										SNew(SBox)
										.Padding(FMargin(20,0))
										[
											SNew(SImage)
											.Image(&LeftMenuStyle->ShoppingLogoImage)
										]
										
									]
								]
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





FText SMyGlobalMenuUI::GetUserName() const
{
	
	return LOCTEXT("UserName", "翱翔的");
}
#undef LOCTEXT_NAMESPACE
FReply SMyGlobalMenuUI::SetLeftMenuVisible()
{
	LittleLeftMenuVisiblility = EVisibility::Hidden;
	if (LeftMenuVisiblility == EVisibility::Visible)
	{
		LeftMenuVisiblility = EVisibility::Hidden;
	}
	else
	{
		LeftMenuVisiblility = EVisibility::Visible;
	}
	return FReply::Handled();
}

FReply SMyGlobalMenuUI::SetLittleLeftMenuHidden()
{
	LittleLeftMenuVisiblility = EVisibility::Hidden;
	LeftMenuVisiblility = EVisibility::Visible;
	return FReply::Handled();
}

FReply SMyGlobalMenuUI::SetLittleLeftMenuVisible()
{	

	LittleLeftMenuVisiblility=EVisibility::Visible;
	LeftMenuVisiblility = EVisibility::Hidden;
	return FReply::Handled();

}

FReply SMyGlobalMenuUI::QuitMyGame()
{
	UKismetSystemLibrary::QuitGame(OwnerHUD->GetWorld(), OwnerHUD->getMyController(), EQuitPreference::Quit);
	return FReply::Handled();
}

EVisibility SMyGlobalMenuUI::GetLeftMenuVisibility() const
{

	return LeftMenuVisiblility;
}

EVisibility SMyGlobalMenuUI::GetLittleLeftMenuVisibility() const
{
	return LittleLeftMenuVisiblility;
}


FReply SMyGlobalMenuUI::ChangeTextColor()
{
	return FReply::Handled();
}

void SMyGlobalMenuUI::OnSearchChanged(const FText& InFilterText)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("OnSearchChanged"));
	}
}

void SMyGlobalMenuUI::OnSearchCommitted(const FText& InFilterText, ETextCommit::Type InCommitType)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("OnSearchCommitted"));
	}
}



//TSharedRef< SWidget > SMyGlobalMenuUI::CreateIteam(const FShoppingCategoryInfo& Info)
//{
//	return SNew(SCheckBox)
//		.OnCheckStateChanged(this,&SMyGlobalMenuUI::OnIteamChanged, Info.DisplayName)
//
//		[
//			SNew(SBox)
//			.HeightOverride(40)
//			[
//				SNew(SButton)
//				.ButtonStyle(&LeftMenuStyle->ShoppingLogoButtonStyle)
//				[
//					SNew(SHorizontalBox)
//					+SHorizontalBox::Slot()
//					.AutoWidth()
//					[
//						SNew(SBox)
//						.WidthOverride(50)
//						.Padding(FMargin(5,0))
//						[
//							SNew(SImage)
//							.Image(&LeftMenuStyle->ShoppingLogoImage)
//						]
//					]
//					+SHorizontalBox::Slot()
//					.AutoWidth()
//					[
//						SNew(SBox)
//						.WidthOverride(100)
//						.VAlign(VAlign_Center)
//						[
//							SNew(STextBlock)
//							.TextStyle(&LeftMenuStyle->ShoppingLogoTextStyle)
//							.Text(FText::FromString("Tool4"))
//						]
//					]
//				]
//			]
//		];
//
//
//
//
//}
//
//void SMyGlobalMenuUI::OnIteamChanged(ECheckBoxState NewSate, FName DisplayName)
//{
//
//}
//

