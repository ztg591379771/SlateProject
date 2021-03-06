// Fill out your copyright notice in the Description page of Project Settings.

#include "MySComboButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "MyGlobalStyle.h"
#include "MyGlobalMenuUI.h"
#include "MyMenuStyle.h"


void SMySComboButton::Construct(const FArguments& InArgs)
{

	


	check(InArgs._ComboButtonStyle);
	//style
	ComboButtonStyle= &FMyMenuStyle::Get().GetWidgetStyle<FMyGlobalStyle>("MyGlobalStyle");
	// Work out which values we should use based on whether we were given an override, or should use the style's version
	const FButtonStyle* const OurButtonStyle = &(ComboButtonStyle->MyComboButtonStyle);

	MenuBorderBrush = &(ComboButtonStyle->MyComboMenuBorderBrush);
	MenuBorderPadding = ComboButtonStyle->MyComboMenuBorderPadding;

	OnComboBoxOpened = InArgs._OnComboBoxOpened;
	ContentWidgetPtr = InArgs._MenuContent.Widget;
	bIsFocusable = InArgs._IsFocusable;

	//-------------------------------------------------user-define-------------------------------------------
	DefaultImage = InArgs._DefaultImage;
	HoveredImage = InArgs._HoveredImage;


	TSharedPtr<SHorizontalBox> HBox;

	SMenuAnchor::Construct(SMenuAnchor::FArguments()
		.Placement(InArgs._MenuPlacement)
		.Method(InArgs._Method)
		.OnMenuOpenChanged(InArgs._OnMenuOpenChanged)
		.OnGetMenuContent(InArgs._OnGetMenuContent)
		.IsCollapsedByParent(InArgs._CollapseMenuOnParentFocus)
		[
			SNew(SBox)
			.WidthOverride(150)
			[
				SNew(SButton)
				.ButtonStyle(OurButtonStyle)
				.ClickMethod(EButtonClickMethod::MouseDown)
				.OnClicked(this, &SMySComboButton::OnButtonClicked)
				.ContentPadding(FMargin(1))
				.ForegroundColor(InArgs._ForegroundColor)
				.ButtonColorAndOpacity(InArgs._ButtonColorAndOpacity)
				.IsFocusable(InArgs._IsFocusable)
				[
					// Button and down arrow on the right
					// +----+-----------------+
					// |  v |  Content		  |
					// +----+-----------------+
					SAssignNew(HBox, SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.Padding(FMargin(5,15,8,15))
					[
						SNew(SImage)
						.Visibility(InArgs._HasDownArrow ? EVisibility::Visible : EVisibility::Collapsed)
						.Image(this,&SMySComboButton::GetMyImage)
						//.Image(&InArgs._ComboButtonStyle->DownArrowImage)
						// Inherit tinting from parent
						//. ColorAndOpacity(FSlateColor::UseForeground())
					]
					+ SHorizontalBox::Slot()
					.Expose(ButtonContentSlot)
					.FillWidth(1)
					.HAlign(InArgs._HAlign)
					.VAlign(InArgs._VAlign)
					[
						InArgs._ButtonContent.Widget
					]
				]
			]
		]
	);


	// The menu that pops up when we press the button.
	// We keep this content around, and then put it into a new window when we need to pop
	// it up.
	SetMenuContent(InArgs._MenuContent.Widget);
}

FReply SMySComboButton::OnButtonClicked()
{
	// Button was clicked; show the popup.
	// Do nothing if clicking on the button also dismissed the menu, because we will end up doing the same thing twice.
	// Don't explicitly focus the menu, here, we're going to do it in the button reply so that it's properly focused
	// to the correct user.
	SetIsOpen(ShouldOpenDueToClick(), false);

	// If the menu is open, execute the related delegate.
	if (IsOpen() && OnComboBoxOpened.IsBound())
	{
		OnComboBoxOpened.Execute();
	}

	// Focusing any newly-created widgets must occur after they have been added to the UI root.
	FReply ButtonClickedReply = FReply::Handled();

	if (bIsFocusable)
	{
		TSharedPtr<SWidget> WidgetToFocus = WidgetToFocusPtr.Pin();
		if (!WidgetToFocus.IsValid())
		{
			// no explicitly focused widget, try to focus the content
			WidgetToFocus = MenuContent;
		}

		if (!WidgetToFocus.IsValid())
		{
			// no content, so try to focus the original widget set on construction
			WidgetToFocus = ContentWidgetPtr.Pin();
		}

		if (WidgetToFocus.IsValid())
		{
			ButtonClickedReply.SetUserFocus(WidgetToFocus.ToSharedRef(), EFocusCause::SetDirectly);
		}
	}
	
	return ButtonClickedReply;
}

FReply SMySComboButton::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Reply = FReply::Unhandled();
	if (InKeyEvent.GetKey() == EKeys::Virtual_Accept)
	{
		// Handle menu open with controller.
		Reply = OnButtonClicked();
	}

	return Reply;
}


const FSlateBrush* SMySComboButton::GetMyImage() const
{
	if (IsHovered())
	{
		return HoveredImage;
	}
	else
	{
		return DefaultImage;
	}
}





void SMySComboButton::SetMenuContent(TSharedRef<SWidget> InContent)
{

	WrappedContent = MenuContent =
		SNew(SBorder)
		.BorderImage(MenuBorderBrush)
		.Padding(MenuBorderPadding)
		[
			InContent
		];
}

void SMySComboButton::SetOnGetMenuContent(FOnGetContent InOnGetMenuContent)
{
	OnGetMenuContent = InOnGetMenuContent;
}
