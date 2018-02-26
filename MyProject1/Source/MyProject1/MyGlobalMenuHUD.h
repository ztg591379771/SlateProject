// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyGlobalMenuHUD.generated.h"

/**
 * 2. the Windows --> Widgets
 */
UCLASS()
class MYPROJECT1_API AMyGlobalMenuHUD : public AHUD
{
	GENERATED_BODY()
	
	//Initialize 
	//3.
	virtual void PostInitializeComponents() override;
	
	//4.
	TSharedPtr<class SMyGlobalMenuUI> MyGlobalMenuUI;
public:
	APlayerController* getMyController();

};
