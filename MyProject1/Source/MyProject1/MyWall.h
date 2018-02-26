// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyWall.generated.h"

UCLASS()
class MYPROJECT1_API AMyWall : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* MyWallRoot;
	
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MyWallMesh;
	
public:	
	// Sets default values for this actor's properties
	AMyWall();
	//基础材质
	UPROPERTY()
	class UMaterial* BaseMaterial;

	// 想要替换的材质
	//UPROPERTY()
	//class UMaterialInstance* ChangeMaterial;

	UMaterialInstance* ArrayMaterial[2];

	//当墙被点击的事件
	UFUNCTION()
	void WallClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	//处理点击事件
	void HandleClicked();
	//是否高亮
	void Highlight(bool bOn);

public:	
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return MyWallRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetMyWallMesh() const { return MyWallMesh; }

	
	
};
