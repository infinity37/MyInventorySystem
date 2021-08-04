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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 MaxAmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 AmmoInChip;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<int32> AttachmentType;

	void EquipItem() override;

	void UnEquipItem() override;

	bool IsEquiped() override;

	UFUNCTION(BlueprintCallable)
		void Reload();

	void SetAmmoInChip(int32 aic);

	void SetMaxAmmoCount(int32 mac);

	UFUNCTION(Server, Reliable)
		void ServerSetAmmoInChip(int32 aic);

	UFUNCTION(Server, Reliable)
		void ServerSetMaxAmmoCount(int32 mac);

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
};
