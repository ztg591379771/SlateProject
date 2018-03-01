// Fill out your copyright notice in the Description page of Project Settings.

#include "MyButton.h"
#include "SlateBasics.h"

void SMyButton::Construct(const FArguments& InArgs)
{
	bIsPressed = false;

	SBorder::Construct(SBorder::FArguments()
		.ContentScale(InArgs._ContentScale)
		.DesiredSizeScale(InArgs._DesiredSizeScale)
		.BorderBackgroundColor(InArgs._ButtonColorAndOpacity)
		.ForegroundColor(InArgs._ForegroundColor)
		.BorderImage(this, &SMyButton::GetBorder)
		.HAlign(InArgs._HAlign)
		.VAlign(InArgs._VAlign)
		.Padding(TAttribute<FMargin>(this, &SMyButton::GetCombinedPadding))
		.ShowEffectWhenDisabled(TAttribute<bool>(this, &SMyButton::GetShowDisabledEffect))
		[
			SNew(STextBlock)
			.Text(InArgs._Text)
			.ColorAndOpacity(this,&SMyButton::GetMyTextColor)
			.Font(FSlateFontInfo("ËÎÌו", 16))
			.TextShapingMethod(InArgs._TextShapingMethod)
			.TextFlowDirection(InArgs._TextFlowDirection)
		]
	);
	ContentPadding = InArgs._ContentPadding;

	SetButtonStyle(InArgs._ButtonStyle);

	bIsFocusable = InArgs._IsFocusable;

	OnClicked = InArgs._OnClicked;
	OnPressed = InArgs._OnPressed;
	OnReleased = InArgs._OnReleased;
	OnHovered = InArgs._OnHovered;
	OnUnhovered = InArgs._OnUnhovered;

	ClickMethod = InArgs._ClickMethod;
	TouchMethod = InArgs._TouchMethod;
	PressMethod = InArgs._PressMethod;

	HoveredSound = InArgs._HoveredSoundOverride.Get(Style->HoveredSlateSound);
	PressedSound = InArgs._PressedSoundOverride.Get(Style->PressedSlateSound);

}

int32 SMyButton::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	bool bEnabled = ShouldBeEnabled(bParentEnabled);
	bool bShowDisabledEffect = GetShowDisabledEffect();

	const FSlateBrush* BrushResource = !bShowDisabledEffect && !bEnabled ? DisabledImage : GetBorder();

	ESlateDrawEffect DrawEffects = bShowDisabledEffect && !bEnabled ? ESlateDrawEffect::DisabledEffect : ESlateDrawEffect::None;

	if (BrushResource && BrushResource->DrawAs != ESlateBrushDrawType::NoDrawType)
	{
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			BrushResource,
			MyClippingRect,
			DrawEffects,
			BrushResource->GetTint(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint() * BorderBackgroundColor.Get().GetColor(InWidgetStyle)
		);
	}

	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect.IntersectionWith(AllottedGeometry.GetClippingRect()), OutDrawElements, LayerId, InWidgetStyle, bEnabled);
}

FMargin SMyButton::GetCombinedPadding() const
{
	return (IsPressed())
		? ContentPadding.Get() + PressedBorderPadding
		: ContentPadding.Get() + BorderPadding;
}

bool SMyButton::GetShowDisabledEffect() const
{
	return DisabledImage->DrawAs == ESlateBrushDrawType::NoDrawType;
}

/** @return An image that represents this button's border*/
const FSlateBrush* SMyButton::GetBorder() const
{
	if (!GetShowDisabledEffect() && !IsEnabled())
	{
		return DisabledImage;
	}
	else if (IsPressed())
	{
		return PressedImage;
	}
	else if (IsHovered())
	{
		return HoverImage;
	}
	else
	{
		return NormalImage;
	}
}
bool SMyButton::SupportsKeyboardFocus() const
{
	// Buttons are focusable by default
	return bIsFocusable;
}


void SMyButton::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	SBorder::OnFocusLost(InFocusEvent);

	Release();
}

FReply SMyButton::OnKeyDown(const FGeometry & MyGeometry, const FKeyEvent & InKeyEvent)
{
	FReply Reply = FReply::Unhandled();

	if (IsEnabled() && (InKeyEvent.GetKey() == EKeys::Enter || InKeyEvent.GetKey() == EKeys::SpaceBar || InKeyEvent.GetKey() == EKeys::Virtual_Accept))
	{
		Press();
		if (PressMethod == EButtonPressMethod::ButtonPress)
		{
			//execute our "OnClicked" delegate, and get the reply
			Reply = OnClicked.IsBound() ? OnClicked.Execute() : FReply::Handled();

			//You should ALWAYS handle the OnClicked event.
			ensure(Reply.IsEventHandled() == true);
		}
		else
		{
			Reply = FReply::Handled();
		}
	}
	else
	{
		Reply = SBorder::OnKeyDown(MyGeometry, InKeyEvent);
	}

	//return the constructed reply
	return Reply;
}





FReply SMyButton::OnKeyUp(const FGeometry & MyGeometry, const FKeyEvent & InKeyEvent)
{
	FReply Reply = FReply::Unhandled();

	if (IsEnabled() && (InKeyEvent.GetKey() == EKeys::Enter || InKeyEvent.GetKey() == EKeys::SpaceBar || InKeyEvent.GetKey() == EKeys::Virtual_Accept))
	{
		const bool bWasPressed = bIsPressed;

		Release();

		//@Todo Slate: This should check focus, however we don't have that API yet, will be easier when focus is unified.
		if (PressMethod == EButtonPressMethod::ButtonRelease || (PressMethod == EButtonPressMethod::DownAndUp && bWasPressed))
		{
			//execute our "OnClicked" delegate, and get the reply
			Reply = OnClicked.IsBound() ? OnClicked.Execute() : FReply::Handled();

			//You should ALWAYS handle the OnClicked event.
			ensure(Reply.IsEventHandled() == true);
		}
		else
		{
			Reply = FReply::Handled();
		}
	}

	//return the constructed reply
	return Reply;
	



}

FReply SMyButton::OnMouseButtonDown(const FGeometry & MyGeometry, const FPointerEvent & MouseEvent)
{
	FReply Reply = FReply::Unhandled();
	if (IsEnabled() && (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || MouseEvent.IsTouchEvent()))
	{
		Press();

		if (ClickMethod == EButtonClickMethod::MouseDown)
		{
			//get the reply from the execute function
			Reply = OnClicked.IsBound() ? OnClicked.Execute() : FReply::Handled();

			//You should ALWAYS handle the OnClicked event.
			ensure(Reply.IsEventHandled() == true);
		}
		else if (IsPreciseTapOrClick(MouseEvent))
		{
			// do not capture the pointer for precise taps or clicks
			// 
		}
		else
		{
			//we need to capture the mouse for MouseUp events
			Reply = FReply::Handled().CaptureMouse(AsShared());
		}
	}

	Invalidate(EInvalidateWidget::Layout);

	//return the constructed reply
	return Reply;
}

FReply SMyButton::OnMouseButtonDoubleClick(const FGeometry & InMyGeometry, const FPointerEvent & InMouseEvent)
{
	return OnMouseButtonDown(InMyGeometry, InMouseEvent);
}

FReply SMyButton::OnMouseButtonUp(const FGeometry & MyGeometry, const FPointerEvent & MouseEvent)
{
	FReply Reply = FReply::Unhandled();
	const bool bMustBePressed = ClickMethod == EButtonClickMethod::DownAndUp || IsPreciseTapOrClick(MouseEvent);
	const bool bMeetsPressedRequirements = (!bMustBePressed || (bIsPressed && bMustBePressed));

	if (bMeetsPressedRequirements && IsEnabled() && (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || MouseEvent.IsTouchEvent()))
	{
		Release();

		if (ClickMethod == EButtonClickMethod::MouseDown)
		{
			// NOTE: If we're configured to click on mouse-down/precise-tap, then we never capture the mouse thus
			//       may never receive an OnMouseButtonUp() call.  We make sure that our bIsPressed
			//       state is reset by overriding OnMouseLeave().
		}
		else
		{
			bool bEventOverButton = IsHovered();
			if (!bEventOverButton && MouseEvent.IsTouchEvent())
			{
				bEventOverButton = MyGeometry.IsUnderLocation(MouseEvent.GetScreenSpacePosition());
			}
			if (bEventOverButton)
			{
				// If we asked for a precise tap, all we need is for the user to have not moved their pointer very far.
				const bool bTriggerForTouchEvent = IsPreciseTapOrClick(MouseEvent);

				// If we were asked to allow the button to be clicked on mouse up, regardless of whether the user
				// pressed the button down first, then we'll allow the click to proceed without an active capture
				const bool bTriggerForMouseEvent = (ClickMethod == EButtonClickMethod::MouseUp || HasMouseCapture());

				if ((bTriggerForTouchEvent || bTriggerForMouseEvent) && OnClicked.IsBound() == true)
				{
					Reply = OnClicked.Execute();
				}
			}
		}

		//If the user of the button didn't handle this click, then the button's
		//default behavior handles it.
		if (Reply.IsEventHandled() == false)
		{
			Reply = FReply::Handled();
		}
	}

	//If the user hasn't requested a new mouse captor and the button still has mouse capture,
	//then the default behavior of the button is to release mouse capture.
	if (Reply.GetMouseCaptor().IsValid() == false && HasMouseCapture())
	{
		Reply.ReleaseMouseCapture();
	}

	Invalidate(EInvalidateWidget::Layout);

	return Reply;
}

FReply SMyButton::OnMouseMove(const FGeometry & MyGeometry, const FPointerEvent & MouseEvent)
{
	const float SlateDragStartDistance = FSlateApplication::Get().GetDragTriggerDistance();
	if (IsPreciseTapOrClick(MouseEvent) && MouseEvent.GetCursorDelta().SizeSquared() > (SlateDragStartDistance*SlateDragStartDistance))
	{
		Release();
	}
	return FReply::Unhandled();
}

void SMyButton::OnMouseEnter(const FGeometry & MyGeometry, const FPointerEvent & MouseEvent)
{
	if (IsEnabled())
	{
		PlayHoverSound();
	}

	SBorder::OnMouseEnter(MyGeometry, MouseEvent);

	OnHovered.ExecuteIfBound();

	Invalidate(EInvalidateWidget::Layout);
}

void SMyButton::OnMouseLeave(const FPointerEvent & MouseEvent)
{
	// Call parent implementation
	SWidget::OnMouseLeave(MouseEvent);

	// If we're setup to click on mouse-down, then we never capture the mouse and may not receive a
	// mouse up event, so we need to make sure our pressed state is reset properly here
	if (ClickMethod == EButtonClickMethod::MouseDown || IsPreciseTapOrClick(MouseEvent))
	{
		Release();
	}

	OnUnhovered.ExecuteIfBound();

	Invalidate(EInvalidateWidget::Layout);
}


void SMyButton::Press()
{
	if (!bIsPressed)
	{
		bIsPressed = true;

		PlayPressedSound();

		OnPressed.ExecuteIfBound();
	}
}


void SMyButton::Release()
{
	if (bIsPressed)
	{
		bIsPressed = false;
		OnReleased.ExecuteIfBound();
	}
}


bool SMyButton::IsInteractable() const
{
	return IsEnabled();
}

bool SMyButton::IsPreciseTapOrClick(const FPointerEvent& MouseEvent) const
{
	return (TouchMethod == EButtonTouchMethod::PreciseTap && MouseEvent.IsTouchEvent()) ||
		(ClickMethod == EButtonClickMethod::PreciseClick && !MouseEvent.IsTouchEvent());
}
void SMyButton::PlayPressedSound() const
{
	FSlateApplication::Get().PlaySound(PressedSound);
}

void SMyButton::PlayHoverSound() const
{
	FSlateApplication::Get().PlaySound(HoveredSound);
}

FVector2D SMyButton::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	// When there is no widget in the button, it sizes itself based on
	// the border image specified by the style.
	if (ChildSlot.GetWidget() == SNullWidget::NullWidget)
	{
		return GetBorder()->ImageSize;
	}
	else
	{
		return SBorder::ComputeDesiredSize(LayoutScaleMultiplier);
	}
}
void SMyButton::SetContentPadding(const TAttribute<FMargin>& InContentPadding)
{
	ContentPadding = InContentPadding;
}

void SMyButton::SetHoveredSound(TOptional<FSlateSound> InHoveredSound)
{
	HoveredSound = InHoveredSound.Get(Style->HoveredSlateSound);
}



void SMyButton::SetPressedSound(TOptional<FSlateSound> InPressedSound)
{
	PressedSound = InPressedSound.Get(Style->PressedSlateSound);

}

void SMyButton::SetOnClicked(FOnClicked InOnClicked)
{
	OnClicked = InOnClicked;
}

void SMyButton::SetOnHovered(FSimpleDelegate InOnHovered)
{
	OnHovered = InOnHovered;

}

void SMyButton::SetOnUnhovered(FSimpleDelegate InOnUnhovered)
{
	OnUnhovered = InOnUnhovered;

}

void SMyButton::SetButtonStyle(const FButtonStyle* ButtonStyle)
{
	Style = ButtonStyle;

	NormalImage = &Style->Normal;
	HoverImage = &Style->Hovered;
	PressedImage = &Style->Pressed;
	DisabledImage = &Style->Disabled;

	BorderPadding = Style->NormalPadding;
	PressedBorderPadding = Style->PressedPadding;

	HoveredSound = Style->HoveredSlateSound;
	PressedSound = Style->PressedSlateSound;
}

FSlateColor SMyButton::GetMyTextColor() const
{
	if (IsHovered())
	{
		return FLinearColor::White;
	}
	else
	{
		return FLinearColor::Black;
	}
}



