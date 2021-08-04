// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BagItem.h"
#include "MyBagItem_Avatar.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AMyBagItem_Avatar : public ABagItem
{
	GENERATED_BODY()
public:

	AMyBagItem_Avatar();

	void EquipItem() override;

	void UnEquipItem() override;

	bool IsEquiped() override;
};
