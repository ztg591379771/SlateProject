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
	//��������
	UPROPERTY()
	class UMaterial* BaseMaterial;

	// ��Ҫ�滻�Ĳ���
	//UPROPERTY()
	//class UMaterialInstance* ChangeMaterial;

	UMaterialInstance* ArrayMaterial[2];

	//��ǽ��������¼�
	UFUNCTION()
	void WallClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	//�������¼�
	void HandleClicked();
	//�Ƿ����
	void Highlight(bool bOn);

public:	
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return MyWallRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetMyWallMesh() const { return MyWallMesh; }

	
	
};
