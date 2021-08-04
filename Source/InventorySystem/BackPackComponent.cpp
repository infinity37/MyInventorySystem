// Fill out your copyright notice in the Description page of Project Settings.


#include "BackPackComponent.h"
#include "MyGameState.h"
#include "teststruct.h"
#include "MyBagItem_Ammo.h"
#include "MyBagItem_Attachment.h"
#include "MyBagItem_Avatar.h"
#include "MyBagItem_Consumable.h"
#include "MyBagItem_Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "PickUps.h"
#include "InventorySystemCharacter.h"

// Sets default values for this component's properties
UBackPackComponent::UBackPackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Owner = NULL;
	BackPackSize = 100;
	CurrentWeight = 0;
	WeaponSlot.Init(NULL, 2);
	AttachmentSlot.Init(NULL, 4);
	AvatarSlot.Init(NULL, 3);
	// ...
}


// Called when the game starts
void UBackPackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBackPackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBackPackComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UBackPackComponent, CurrentWeight, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UBackPackComponent, NormalSpace, COND_OwnerOnly);
}

bool UBackPackComponent::CanAddItem(int32 ItemTypeId, int32 Count) {
	AMyGameState* GameState = Cast<AMyGameState>(GetWorld()->GetGameState());
	UItemInfoTable* ItemTable = GameState->GetItemInfoTable();
	UItemInfo* ItemToAdd = ItemTable->GetItemInfoById(ItemTypeId);

	if (IsNewItem(ItemTypeId)) {
		return CurrentWeight + ItemToAdd->ItemWeight * Count <= BackPackSize;
	}
	else {
		bool cond1 = CurrentWeight + ItemToAdd->ItemWeight * Count <= BackPackSize;
		bool cond2 = NormalSpace[ItemTypeId]->ItemCount + Count <= ItemToAdd->ItemMaxCount;
		return (cond1 && cond2);
	}
	
	return true;
}

void UBackPackComponent::AddItem(int32 ItemTypeId, int32 Count, AActor* otherActor) {
	if (IsNewItem(ItemTypeId))
		AddNewItem(ItemTypeId, Count, otherActor);
	else AddOldItem(ItemTypeId, Count);
}

bool UBackPackComponent::IsNewItem(int32 ItemTypeId) {
	return (!NormalSpace.Contains(ItemTypeId));
}

void UBackPackComponent::AddNewItem(int32 ItemTypeId, int32 Count, AActor* otherActor) {
	AMyGameState* GameState = Cast<AMyGameState>(GetWorld()->GetGameState());
	UItemInfoTable* ItemTable = GameState->GetItemInfoTable();
	UItemInfo* ItemToAdd = ItemTable->GetItemInfoById(ItemTypeId);

	ABagItem* newitem;
	switch (ItemTypeId / 100)
	{
	case 1: 
	{
		AMyBagItem_Ammo* ammoitem = GetWorld()->SpawnActor<AMyBagItem_Ammo>();
		newitem = Cast<ABagItem>(ammoitem);
		break;
	}
	case 2:
	{
		AMyBagItem_Attachment* attitem = GetWorld()->SpawnActor<AMyBagItem_Attachment>();
		newitem = Cast<ABagItem>(attitem);
		break;
	}
	case 3:
	{
		AMyBagItem_Avatar* avaitem = GetWorld()->SpawnActor<AMyBagItem_Avatar>();
		newitem = Cast<ABagItem>(avaitem);
		break;
	}
	case 4:
	{
		AMyBagItem_Consumable* conitem = GetWorld()->SpawnActor<AMyBagItem_Consumable>();
		newitem = Cast<ABagItem>(conitem);
		break;
	}
	case 5:
	{
		AMyBagItem_Weapon* weaponitem = GetWorld()->SpawnActor<AMyBagItem_Weapon>();
		FWeaponInfo WeaponToAdd = ItemTable->GetWeaponInfoById(ItemTypeId);
		weaponitem->Damage = WeaponToAdd.Damage;
		weaponitem->AmmoType = WeaponToAdd.AmmoType;
		weaponitem->AmmoInChip = 0;
		weaponitem->MaxAmmoCount = WeaponToAdd.MaxAmmoCount;
		weaponitem->AttachmentType = WeaponToAdd.AttachmentType;
		newitem = Cast<ABagItem>(weaponitem);
		break;
	}
	default:
	{
		newitem = GetWorld()->SpawnActor<ABagItem>();
		break;
	}
	}
	newitem->ItemInfo = ItemToAdd;
	newitem->ItemTypeId = ItemTypeId;
	newitem->SetItemOwner(otherActor);
	newitem->AddItem(Count);
	NormalSpace.Add(ItemTypeId, newitem);
	CurrentWeight += Count * ItemToAdd->ItemWeight;
}

void UBackPackComponent::AddOldItem(int32 ItemTypeId, int32 Count) {
	NormalSpace[ItemTypeId]->AddItem(Count);
	CurrentWeight += Count * ( NormalSpace[ItemTypeId]->ItemInfo->ItemWeight );
}

void UBackPackComponent::UseItem(int32 ItemTypeId) {
	ServerUseItem(ItemTypeId);
	ClientUseItem(ItemTypeId);
}

void UBackPackComponent::ServerUseItem_Implementation(int32 ItemTypeId) {
	if ((ItemTypeId / 100) % 10 == 4) {
		AMyBagItem_Consumable* myItem = Cast<AMyBagItem_Consumable>(NormalSpace[ItemTypeId]);
		myItem->UseItem();
		CurrentWeight -= myItem->ItemInfo->ItemWeight;
		if (myItem->ItemCount <= 0) {
			NormalSpace.Remove(ItemTypeId);
			myItem->Destroy();
		}
	}
	else if ((ItemTypeId / 100) % 10 == 1) {
		AMyBagItem_Ammo* myItem = Cast<AMyBagItem_Ammo>(NormalSpace[ItemTypeId]);
		myItem->UseItem();
		CurrentWeight -= myItem->ItemInfo->ItemWeight;
		if (myItem->ItemCount <= 0) {
			NormalSpace.Remove(ItemTypeId);
			myItem->Destroy();
		}
	}
}

void UBackPackComponent::ClientUseItem_Implementation(int32 ItemTypeId) {
	if ((ItemTypeId / 100) % 10 == 4) {
		AMyBagItem_Consumable* myItem = Cast<AMyBagItem_Consumable>(NormalSpace[ItemTypeId]);
		myItem->ItemCount -= 1;
		if (myItem->ItemCount <= 0) {
			NormalSpace.Remove(ItemTypeId);
			myItem->Destroy();
		}
	}
	else if ((ItemTypeId / 100) % 10 == 1) {
		AMyBagItem_Ammo* myItem = Cast<AMyBagItem_Ammo>(NormalSpace[ItemTypeId]);
		myItem->ItemCount -= 1;
		if (myItem->ItemCount <= 0) {
			NormalSpace.Remove(ItemTypeId);
			myItem->Destroy();
		}
	}
}

void UBackPackComponent::DropItem(int32 ItemTypeId, int32 Count) {
	ServerDropItem(ItemTypeId, Count);
	ClientDropItem(ItemTypeId, Count);
}

void UBackPackComponent::ServerDropItem_Implementation(int32 ItemTypeId, int32 Count) {
	if (!NormalSpace.Contains(ItemTypeId))return;
	if (NormalSpace[ItemTypeId]->ItemCount < Count)return;
	NormalSpace[ItemTypeId]->ItemCount = NormalSpace[ItemTypeId]->ItemCount - Count;
	CurrentWeight -= Count * NormalSpace[ItemTypeId]->ItemInfo->ItemWeight;
	AInventorySystemCharacter* myplayer = Cast<AInventorySystemCharacter>(NormalSpace[ItemTypeId]->ItemBelongTo);
	if (NormalSpace[ItemTypeId]->ItemCount <= 0) {
		NormalSpace[ItemTypeId]->Destroy();
		NormalSpace.Remove(ItemTypeId);
	}
	myplayer->GenerateNewPickUp(ItemTypeId, Count);
}

void UBackPackComponent::ClientDropItem_Implementation(int32 ItemTypeId, int32 Count) {
	NormalSpace[ItemTypeId]->ItemCount = NormalSpace[ItemTypeId]->ItemCount - Count;
	CurrentWeight -= Count * NormalSpace[ItemTypeId]->ItemInfo->ItemWeight;
	if (NormalSpace[ItemTypeId]->ItemCount <= 0) {
		NormalSpace[ItemTypeId]->Destroy();
		NormalSpace.Remove(ItemTypeId);
	}
}

bool UBackPackComponent::AddToAttachmentSlot(int32 ItemTypeId, int32 pos) {
	if (!NormalSpace.Contains(ItemTypeId)) return false;
	if (WeaponSlot[pos] == NULL) return false;
	AMyBagItem_Weapon* ParentWeapon = Cast<AMyBagItem_Weapon>(WeaponSlot[pos]);
	pos = pos << 1 | ((ItemTypeId / 10) & 1);
	if (ParentWeapon->AttachmentType[(ItemTypeId / 10) & 1] != ItemTypeId)return false;//检查是否可以放进来

	AMyBagItem_Attachment* AttItem = Cast<AMyBagItem_Attachment>(NormalSpace[ItemTypeId]);
	if (AttachmentSlot[pos] != NULL) {
		RemoveFromAttachmentSlot(pos);
	}
	
	AttachmentSlot[pos] = NormalSpace[ItemTypeId];
	AttItem->SetParentWeapon(Cast<AActor>(ParentWeapon));
	AttItem->SetInSlotState(pos);
	AttItem->EquipItem();
	return true;
}

bool UBackPackComponent::AddToAvatarSlot(int32 ItemTypeId, int32 pos) {
	if (!NormalSpace.Contains(ItemTypeId)) return false;
	AMyBagItem_Avatar* AvaItem = Cast<AMyBagItem_Avatar>(NormalSpace[ItemTypeId]);
	if (AvatarSlot[pos] != NULL) {
		RemoveFromAvatarSlot(pos);
	}
	AvatarSlot[pos] = NormalSpace[ItemTypeId];
	AvaItem->EquipItem();
	AvaItem->SetInSlotState(pos);
	return true;
}

void UBackPackComponent::AddToWeaponSlot(int32 ItemTypeId, int32 pos) {
	if (!NormalSpace.Contains(ItemTypeId)) return ;
	AMyBagItem_Weapon* WeapItem = Cast<AMyBagItem_Weapon>(NormalSpace[ItemTypeId]);
	if (WeaponSlot[pos] != NULL) {
		RemoveFromWeaponSlot(pos);
	}
	WeaponSlot[pos] = NormalSpace[ItemTypeId];
	WeapItem->SetInSlotState(pos);
	return ;
}

void UBackPackComponent::RemoveFromWeaponSlot(int32 pos) {
	if (WeaponSlot[pos] == NULL) return;
	if (AttachmentSlot[pos << 1]) RemoveFromAttachmentSlot(pos << 1);
	if (AttachmentSlot[pos << 1 | 1])RemoveFromAttachmentSlot(pos << 1 | 1);

	AMyBagItem_Weapon* OldWeapItem = Cast<AMyBagItem_Weapon>(WeaponSlot[pos]);
	if (OldWeapItem->IsEquiped())OldWeapItem->UnEquipItem();
	OldWeapItem->SetInSlotState(-1);
	WeaponSlot[pos] = NULL;
}

void UBackPackComponent::RemoveFromAttachmentSlot(int32 pos) {
	if (AttachmentSlot[pos] == NULL) return;

	AMyBagItem_Attachment* OldAttItem = Cast<AMyBagItem_Attachment>(AttachmentSlot[pos]);
	OldAttItem->UnEquipItem();
	OldAttItem->SetInSlotState(-1);
	AttachmentSlot[pos] = NULL;
}

void UBackPackComponent::RemoveFromAvatarSlot(int32 pos) {
	if (AvatarSlot[pos] == NULL) return;

	AMyBagItem_Avatar* OldAvaItem = Cast<AMyBagItem_Avatar>(AvatarSlot[pos]);
	OldAvaItem->UnEquipItem();
	OldAvaItem->SetInSlotState(-1);
	AvatarSlot[pos] = NULL;
}

void UBackPackComponent::AddAmmoToNormalSpace(int32 ItemTypeId, int32 Count, AActor* otherActor) {
	if (IsNewItem(ItemTypeId)) {
		AMyGameState* GameState = Cast<AMyGameState>(GetWorld()->GetGameState());
		UItemInfoTable* ItemTable = GameState->GetItemInfoTable();
		UItemInfo* ItemToAdd = ItemTable->GetItemInfoById(ItemTypeId);

		ABagItem* newitem;
		AMyBagItem_Ammo* ammoitem = GetWorld()->SpawnActor<AMyBagItem_Ammo>();
		newitem = Cast<ABagItem>(ammoitem);

		newitem->ItemInfo = ItemToAdd;
		newitem->ItemTypeId = ItemTypeId;
		newitem->SetItemOwner(otherActor);
		newitem->AddItem(Count);
		NormalSpace.Add(ItemTypeId, newitem);
	}
	else {
		NormalSpace[ItemTypeId]->AddItem(Count);
	}
}

void UBackPackComponent::OnRepNormalSpaceDebug() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("NormalSpaceReplicated"));
}