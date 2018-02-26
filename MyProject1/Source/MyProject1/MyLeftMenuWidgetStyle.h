// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateWidgetStyleContainerBase.h"
#include "SlateWidgetStyle.h"
#include "SlateBasics.h"
#include "MyLeftMenuWidgetStyle.generated.h"


USTRUCT(BlueprintType)
struct FLeftMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()
	// Stores a list of Brushes we are using (we aren't using any) into OutBrushes.
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;

	// Stores the TypeName for our widget style.
	static const FName TypeName;


	// Retrieves the type name for our global style, which will be used by our Style Set to load the right file. 
	virtual const FName GetTypeName() const override;

	// Allows us to set default values for our various styles. 
	static const FLeftMenuStyle& GetDefault();
	
	//-----------------------------------------set our style----------------

	//--------------------------------------Display Menu-----------------------------------------
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush DisplayRightImage;
	FLeftMenuStyle& SetDisplayRightImage(const FSlateBrush& InDisplayRightImage) { DisplayRightImage = InDisplayRightImage; return *this; }
	
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush DisplayLeftImage;
	FLeftMenuStyle& SetDisplayLeftImage(const FSlateBrush& InDisplayLeftImage) { DisplayLeftImage = InDisplayLeftImage; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle DisplayButtonStyle;
	FLeftMenuStyle& SetDisplayButtonStyle(const FButtonStyle& InDisplayButtonStyle) { DisplayButtonStyle = InDisplayButtonStyle; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FTextBlockStyle DisplayTextStyle;
	FLeftMenuStyle& SetDisplayTextStyle(const FTextBlockStyle& InDisplayTextStyle) { DisplayTextStyle = InDisplayTextStyle; return *this; }



	//-----------------------------------------Shopping------------------------------------------
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush ShoppingLogoImage;
	FLeftMenuStyle& SetShoppingLogoImage(const FSlateBrush& InShoppingLogoImage) { ShoppingLogoImage = InShoppingLogoImage; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FTextBlockStyle ShoppingLogoTextStyle;
	FLeftMenuStyle& SetShoppingLogoTextStyle(const FTextBlockStyle& InShoppingLogoTextStyle) { ShoppingLogoTextStyle = InShoppingLogoTextStyle; return *this; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle ShoppingLogoButtonStyle;
	FLeftMenuStyle& SetShoppingLogoButtonStyle(const FButtonStyle& InShoppingLogoButtonStyle) { ShoppingLogoButtonStyle = InShoppingLogoButtonStyle; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle ShoppingLittleLogoButtonStyle;
	FLeftMenuStyle& SetShoppingLittleLogoButtonStyle(const FButtonStyle& InShoppingLittleLogoButtonStyle) { ShoppingLittleLogoButtonStyle = InShoppingLittleLogoButtonStyle; return *this; }

	//----------------------------------------class and grand--------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FTextBlockStyle ClassTextStyle;
	FLeftMenuStyle& SetClassTextStyle(const FTextBlockStyle& InClassTextStyle) { ClassTextStyle = InClassTextStyle; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle ClassButtonStyle;
	FLeftMenuStyle& SetClassButtonStyle(const FButtonStyle& InClassButtonStyle) { ClassButtonStyle = InClassButtonStyle; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FTextBlockStyle ClassButtonContentTextStyle;
	FLeftMenuStyle& SetClassButtonContentTextStyle(const FTextBlockStyle& InClassButtonContentTextStyle) { ClassButtonContentTextStyle = InClassButtonContentTextStyle; return *this; }

	//-----------------------------------------product style-------------------------------
	// not collected
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush ProductNoCollectImage;
	FLeftMenuStyle& SetProductNoCollectImage(const FSlateBrush& InProductNoCollectImage) { ProductNoCollectImage = InProductNoCollectImage; return *this; }
	
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush ProductCollectedImage;
	FLeftMenuStyle& SetProductCollectedImage(const FSlateBrush& InProductCollectedImage) { ProductCollectedImage = InProductCollectedImage; return *this; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle ProductCollectButtonStyle;
	FLeftMenuStyle& SetProductCollectButtonStyle(const FButtonStyle& InProductCollectButtonStyle) { ProductCollectButtonStyle = InProductCollectButtonStyle; return *this; }

	
	// recommend
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush ProductRecommendImage;
	FLeftMenuStyle& SetProductRecommendImage(const FSlateBrush& InProductRecommendImage) { ProductRecommendImage = InProductRecommendImage; return *this; }

	// product image
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush ProductImage;
	FLeftMenuStyle& SetProductImage(const FSlateBrush& InProductImage) { ProductImage = InProductImage; return *this; }
	//price
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FTextBlockStyle ProductPriceTextStyle;
	FLeftMenuStyle& SetProductPriceTextStyle(const FTextBlockStyle& InProductPriceTextStyle) { ProductPriceTextStyle = InProductPriceTextStyle; return *this; }
	//logo

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle ProductLogoButtonStyle;
	FLeftMenuStyle& SetProductLogoButtonStyle(const FButtonStyle& InProductLogoButtonStyle) { ProductLogoButtonStyle = InProductLogoButtonStyle; return *this; }


	//Apply
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FButtonStyle ProductApplyButtonStyle;
	FLeftMenuStyle& SetProductApplyButtonStyle(const FButtonStyle& InProductApplyButtonStyle) { ProductApplyButtonStyle = InProductApplyButtonStyle; return *this; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FTextBlockStyle ProductApplyTextStyle;
	FLeftMenuStyle& SetProductApplyTextStyle(const FTextBlockStyle& InProductApplyTextStyle) { ProductApplyTextStyle = InProductApplyTextStyle; return *this; }




};

UCLASS()
class MYPROJECT1_API UMyLeftMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()

public:
	// This is our actual Style object. 
	UPROPERTY(EditAnywhere, Category = Appearance, meta = (ShowOnlyInnerProperties))
	FLeftMenuStyle LeftMenuStyle;

	// Retrievs the style that this container manages. 
	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&LeftMenuStyle);
	}
};
