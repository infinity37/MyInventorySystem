// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BagItem.h"
#include "ItemEffect.h"
#include "MyBagItem_Consumable.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AMyBagItem_Consumable : public ABagItem
{
	GENERATED_BODY()

public:
	AMyBagItem_Consumable();

	void UseItem() override;
};
