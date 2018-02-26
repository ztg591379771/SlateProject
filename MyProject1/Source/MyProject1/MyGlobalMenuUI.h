// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SlateBasics.h"
#include "CoreMinimal.h"
#include "MyGlobalMenuHUD.h"
#include "Widgets/SCompoundWidget.h"
#include "MyLeftMenuWidgetStyle.h"
/**
 * 5. show the Main Menu UI --->widgets
 */

struct FShoppingCategoryInfo
{
	FText DisplayName;
	const FSlateBrush* UnCheckedImage;
	const FSlateBrush* CheckedImage;
	bool IsChecked;
};
class MYPROJECT1_API SMyGlobalMenuUI : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SMyGlobalMenuUI)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AMyGlobalMenuHUD>, OwnerHUD)
	SLATE_END_ARGS()

	/*
		6. every widget have Construct
	*/
	void Construct(const FArguments& args);


	/*
		7.the Owner of the Widgets
	*/
	TWeakObjectPtr<AMyGlobalMenuHUD> OwnerHUD;

	/*
		Create a topMenuStyle
	*/
	const struct FMyGlobalStyle* MenuStyle;

	/*
	Create a LeftMenuStyle
	*/
	const struct FLeftMenuStyle* LeftMenuStyle;

	/*
		get User name
	*/
	FText GetUserName() const;

	/*
		set Left MenuVisible
	*/
	FReply SetLeftMenuVisible();

	/*
		set Left MenuVisible
	*/
	FReply SetLittleLeftMenuHidden();

	/*
	set Left MenuVisible
	*/
	FReply SetLittleLeftMenuVisible();

	FReply QuitMyGame();

	/*
		get left Menu Visible
	*/
	EVisibility GetLeftMenuVisibility() const;
	EVisibility GetLittleLeftMenuVisibility() const;
	EVisibility LeftMenuVisiblility;
	EVisibility LittleLeftMenuVisiblility;
public:
	//APawn* Pawn;
private:
	/** Called when the search text changes */
	void OnSearchChanged(const FText& InFilterText);
	void OnSearchCommitted(const FText& InFilterText, ETextCommit::Type InCommitType);

	////Create shopping ItemCategory
	//TSharedRef< SWidget > CreateIteam(const FShoppingCategoryInfo& Info);


	//void OnIteamChanged(ECheckBoxState NewSate, FName DisplayName);
	/////** Get the text that should be highlighted on any items */
	////FText GetHighlightText() const;



};
