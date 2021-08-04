// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBagItem_Weapon.h"
#include "InventorySystemCharacter.h"
#include "MyPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AMyBagItem_Weapon::AMyBagItem_Weapon() {
	Damage = 5;
	MaxAmmoCount = 30;
	AmmoInChip = 0;
	AmmoType = 0;
	AttachmentType.Init(-1, 2);
	AttachmentType[0] = 201;
}

void AMyBagItem_Weapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyBagItem_Weapon, AmmoInChip);
	DOREPLIFETIME(AMyBagItem_Weapon, MaxAmmoCount);
}

void AMyBagItem_Weapon::EquipItem() {
	SetEquipState(true);
	AInventorySystemCharacter* player = Cast<AInventorySystemCharacter>(ItemBelongTo);
	player->SetIntAttribute(AttriName::Damage, Damage);
	player->SetCurrentWeapon(ItemTypeId);
	Reload();
}

void AMyBagItem_Weapon::UnEquipItem() {
	SetEquipState(false);
	AInventorySystemCharacter* player = Cast<AInventorySystemCharacter>(ItemBelongTo);
	player->SetCurrentWeapon(-1);
	player->SetIntAttribute(AttriName::Damage, 1);
	AMyPlayerController* PC = Cast<AMyPlayerController>(player->GetController());
	PC->myBackPack->AddAmmoToNormalSpace(AmmoType, AmmoInChip, player);
	AmmoInChip = 0;
}

void AMyBagItem_Weapon::Reload() {
	AInventorySystemCharacter* player = Cast<AInventorySystemCharacter>(ItemBelongTo);
	AMyPlayerController* PC = Cast<AMyPlayerController>(player->GetController());
	
	int32 MissingAmmo = MaxAmmoCount - AmmoInChip;
	int AmmoInBag = PC->GetItemCountById(AmmoType);
	if (AmmoInBag == 0) return;
	if (AmmoInBag >= MissingAmmo) {
		SetAmmoInChip(MaxAmmoCount);
		PC->myBackPack->NormalSpace[AmmoType]->DecItem(MissingAmmo);
	}
	else {
		SetAmmoInChip(AmmoInChip+AmmoInBag);
		PC->myBackPack->NormalSpace[AmmoType]->DecItem(AmmoInBag);
	}
}

bool AMyBagItem_Weapon::IsEquiped() {
	AInventorySystemCharacter* player = Cast<AInventorySystemCharacter>(ItemBelongTo);
	return player->GetCurrentWeapon() == ItemTypeId;
}

void AMyBagItem_Weapon::SetAmmoInChip(int32 aic) {
	if (aic > MaxAmmoCount)return;
	if (GetLocalRole() < ROLE_Authority) {
		ServerSetAmmoInChip(aic);
	}
	else {
		AmmoInChip = aic;
	}
}

void AMyBagItem_Weapon::ServerSetAmmoInChip_Implementation(int32 aic) {
	SetAmmoInChip(aic);
}

void AMyBagItem_Weapon::SetMaxAmmoCount(int32 mac) {
	if (GetLocalRole() < ROLE_Authority) {
		ServerSetMaxAmmoCount(mac);
	}
	else {
		MaxAmmoCount = mac;
	}
}

void AMyBagItem_Weapon::ServerSetMaxAmmoCount_Implementation(int32 mac) {
	SetMaxAmmoCount(mac);
}