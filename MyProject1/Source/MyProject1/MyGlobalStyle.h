// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "SlateWidgetStyleContainerBase.h"
#include "SlateWidgetStyle.h"
#include "SlateBasics.h"
#include "MyGlobalStyle.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct  FMyGlobalStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()
		FMyGlobalStyle();
	// Stores a list of Brushes we are using (we aren't using any) into OutBrushes.
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	
	// Stores the TypeName for our widget style.
	static const FName TypeName;


	// Retrieves the type name for our global style, which will be used by our Style Set to load the right file. 
	virtual const FName GetTypeName() const override;

	// Allows us to set default values for our various styles. 
	static const FMyGlobalStyle& GetDefault();
	
	//------------------------------------------------------set our style ---------------------------------
	// set the logoImage
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush LogoImage;
	FMyGlobalStyle& SetLogoImage(const FSlateBrush& InLogoImage) { LogoImage = InLogoImage; return *this; }


	//---------------------------------------------------email button--------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle EmailButtonStyle;
	FMyGlobalStyle& SetEmailButtonStyle(const FButtonStyle& InEmailButtonStyle) { EmailButtonStyle = InEmailButtonStyle; return *this; }

	// -------------------------------------------------clothes---------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle ClothesButtonStyle;
	FMyGlobalStyle& SetClothesButtonStyle(const FButtonStyle& InClothesButtonStyle) { ClothesButtonStyle = InClothesButtonStyle; return *this; }

	//--------------------------------------------------personal--------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle PersonalButtonStyle;
	FMyGlobalStyle& SetPersonalButtonStyle(const FButtonStyle& InPersonalButtonStyle) { PersonalButtonStyle = InPersonalButtonStyle; return *this; }

	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush PersonalImage;
	FMyGlobalStyle& SetPersonalImage(const FSlateBrush& InPersonalImage) { PersonalImage = InPersonalImage; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FTextBlockStyle PersonalTextStyle;
	FMyGlobalStyle& SetPersonalTextStyle(const FTextBlockStyle& InPersonalTextStyle) { PersonalTextStyle = InPersonalTextStyle; return *this; }
	//--------------------------------------------------four button Style----------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle RightFourButtonStyle;
	FMyGlobalStyle& SetRightFourButtonStyle(const FButtonStyle& InRightFourButtonStyle) { RightFourButtonStyle = InRightFourButtonStyle; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FTextBlockStyle RightFourTextStyle;
	FMyGlobalStyle& SetRightFourTextStyle(const FTextBlockStyle& InRightFourTextStyle) { RightFourTextStyle = InRightFourTextStyle; return *this; }

	//----------------------------------------------------user name Style-----------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FTextBlockStyle UserNameTextStyle;
	FMyGlobalStyle& SetUserNameTextStyle(const FTextBlockStyle& InUserNameTextStyle) { UserNameTextStyle = InUserNameTextStyle; return *this; }





	//---------------------------------------------MyComboButton Style-------------------------------------
	/**
	* The style to use for our SButton
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle MyComboButtonStyle;
	FMyGlobalStyle& SetMyComboButtonStyle(const FButtonStyle& InMyComboButtonStyle) { MyComboButtonStyle = InMyComboButtonStyle; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle MyComboContentButtonStyle;
	FMyGlobalStyle& SetMyComboContentButtonStyle(const FButtonStyle& InMyComboContentButtonStyle) { MyComboContentButtonStyle = InMyComboContentButtonStyle; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FTextBlockStyle MyComboContentTextStyle;
	FMyGlobalStyle& SetMyComboContentTextStyle(const FTextBlockStyle& InMyComboContentTextStyle) { MyComboContentTextStyle = InMyComboContentTextStyle; return *this; }



	/** Text style */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FTextBlockStyle MyComBoTextStyle;
	FMyGlobalStyle& SetMyComBoTextStyle(const FTextBlockStyle& InMyComBoTextStyle) { MyComBoTextStyle = InMyComBoTextStyle; return *this; }


	///**
	//* Image to use for the default
	//*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	//FSlateBrush MyComboDefaultImage;
	//FMyGlobalStyle& SetMyComboDefaultImage(const FSlateBrush& InMyComboDefaultImage) { MyComboDefaultImage = InMyComboDefaultImage; return *this; }
	///**
	//* Image to use for the Hovered
	//*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	//FSlateBrush MyComboHoveredImage;
	//FMyGlobalStyle& SetMyComboHoveredImage(const FSlateBrush& InMyComboHoveredImage) { MyComboHoveredImage = InMyComboHoveredImage; return *this; }
	/**
	* Brush to use to add a "menu border" around the drop-down content
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FSlateBrush MyComboMenuBorderBrush;
	FMyGlobalStyle& SetMyComboMenuBorderBrush(const FSlateBrush& InMyComboMenuBorderBrush) { MyComboMenuBorderBrush = InMyComboMenuBorderBrush; return *this; }

	/**
	* Padding to use to add a "menu border" around the drop-down content
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FMargin MyComboMenuBorderPadding;
	FMyGlobalStyle& SetMyComboMenuBorderPadding(const FMargin& InMyComboMenuBorderPadding) { MyComboMenuBorderPadding = InMyComboMenuBorderPadding; return *this; }
};










// Provides a widget style container to allow us to edit properties in-editor
UCLASS(hidecategories = Object, MinimalAPI)
class UGlobalStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()
public:
	// This is our actual Style object. 
	UPROPERTY(EditAnywhere, Category = Appearance, meta = (ShowOnlyInnerProperties))
	FMyGlobalStyle MenuStyle;

	// Retrievs the style that this container manages. 
	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&MenuStyle);
	}
};