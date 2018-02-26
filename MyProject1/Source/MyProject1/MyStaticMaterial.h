// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstance.h"


/**
 * 
 */
class MYPROJECT1_API MyStaticMaterial
{
public:
	MyStaticMaterial();
	~MyStaticMaterial();
	UMaterialInstance* MyMaterial[2];
};
