// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Materials/MaterialInstance.h"
#include "MyWallPawn.generated.h"

UCLASS()
class MYPROJECT1_API AMyWallPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyWallPawn();

protected:

	void LeftMouseClick();
	void RightMouseClick();
	void TraceForWall(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class AMyWall* MyWall;

	
public:	
	//class UMaterialInstance* ChangeMaterial;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void TickOnce(FVector2D DropLocalMousePos);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	int MaterialID;
	
	
	TSharedPtr<SWidget> MousePicture;
};
