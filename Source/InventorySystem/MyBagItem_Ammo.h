// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BagItem.h"
#include "MyBagItem_Ammo.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AMyBagItem_Ammo : public ABagItem
{
	GENERATED_BODY()
	
public:
	void UseItem() override;
};
