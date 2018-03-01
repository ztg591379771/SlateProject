// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "SlateWidgetStyle.h"
#include "SlateBasics.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "MyCheckBoxStyle.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FMyLeftCheckBoxStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	// Stores a list of Brushes we are using (we aren't using any) into OutBrushes.
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;

	// Stores the TypeName for our widget style.
	static const FName TypeName;


	// Retrieves the type name for our global style, which will be used by our Style Set to load the right file. 
	virtual const FName GetTypeName() const override;

	// Allows us to set default values for our various styles. 
	static const FMyLeftCheckBoxStyle& GetDefault();


	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush CheckedImage;
	FMyLeftCheckBoxStyle& SetCheckedImage(const FSlateBrush& InCheckedImage) { CheckedImage = InCheckedImage; return *this; }

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush UncheckedImage;
	FMyLeftCheckBoxStyle& SetUncheckedImage(const FSlateBrush& InUncheckedImage) { UncheckedImage = InUncheckedImage; return *this; }

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush CheckedPressedImage;
	FMyLeftCheckBoxStyle& SetCheckedPressedImage(const FSlateBrush& InCheckedPressedImage) { CheckedPressedImage = InCheckedPressedImage; return *this; }

	
	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush NormalImage;
	FMyLeftCheckBoxStyle& SetNormalImage(const FSlateBrush& InNormalImage) { NormalImage = InNormalImage; return *this; }

	UPROPERTY(EditAnywhere, Category = Appearance)
		FSlateBrush HoverImage;
	FMyLeftCheckBoxStyle& SetHoverImage(const FSlateBrush& InHoverImage) { HoverImage = InHoverImage; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		FTextBlockStyle NormalTextStyle;
	FMyLeftCheckBoxStyle& SetNormalTextStyle(const FTextBlockStyle& InNormalTextStyle) { NormalTextStyle = InNormalTextStyle; return *this; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		FTextBlockStyle HoverTextStyle;
	FMyLeftCheckBoxStyle& SetHoverTextStyle(const FTextBlockStyle& InHoverTextStyle) { HoverTextStyle = InHoverTextStyle; return *this; }

};

UCLASS()
class MYPROJECT1_API UMyCheckBoxStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()
	
public:
	// This is our actual Style object. 
	UPROPERTY(EditAnywhere, Category = Appearance, meta = (ShowOnlyInnerProperties))
		FMyLeftCheckBoxStyle MyCheckBoxStyle;

	// Retrievs the style that this container manages. 
	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&MyCheckBoxStyle);
	}
	
	
};
