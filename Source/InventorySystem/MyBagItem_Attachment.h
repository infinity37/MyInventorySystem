// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BagItem.h"
#include "MyBagItem_Attachment.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AMyBagItem_Attachment : public ABagItem
{
	GENERATED_BODY()
public:
	AMyBagItem_Attachment();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		AActor* ParentWeapon;

	void SetParentWeapon(AActor* Weapon);

	UFUNCTION(Server, Reliable)
		void ServerSetParentWeapon(AActor* Weapon);

	void EquipItem() override;

	void UnEquipItem() override;

	bool IsEquiped() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
