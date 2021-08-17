// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BagItem.h"
#include "MyBagItem_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AMyBagItem_Weapon : public ABagItem
{
	GENERATED_BODY()
	
public:
	AMyBagItem_Weapon();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
		int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 MaxAmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RefreshBagUI)
		int32 AmmoInChip;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
		int32 AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
		TArray<int32> AttachmentType;

	void EquipItem() override;

	void UnEquipItem() override;

	bool IsEquiped() override;

	void Reload();

	void SetAmmoInChip(int32 aic);

	void SetMaxAmmoCount(int32 mac);

	void SetDamage(int32 dmg);

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

};
