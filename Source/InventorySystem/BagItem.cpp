// Fill out your copyright notice in the Description page of Project Settings.


#include "BagItem.h"

// Sets default values
ABagItem::ABagItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	ItemBelongTo = NULL;
	ItemCount = 0;
	ItemInSlot = -1;
}

// Called when the game starts or when spawned
void ABagItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABagItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABagItem::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABagItem, ItemCount);
	DOREPLIFETIME(ABagItem, ItemInSlot);
	DOREPLIFETIME(ABagItem, ItemEquiped);
	DOREPLIFETIME(ABagItem, ItemBelongTo);
}

void ABagItem::EquipItem() {

}

void ABagItem::UnEquipItem() {

}

bool ABagItem::IsEquiped() {
	return false;
}

void ABagItem::UseItem() {

}

int32 ABagItem::GetWeight() {
	return ItemInfo->ItemWeight;
}

int32 ABagItem::GetMaxCount() {
	return ItemInfo->ItemMaxCount;
}

FString ABagItem::GetName() {
	return ItemInfo->ItemName;
}

FString ABagItem::GetDescription() {
	return ItemInfo->ItemDescription;
}

void ABagItem::AddItem(int32 Count) {
	if (GetLocalRole() < ROLE_Authority) {
		ServerAddItem(Count);
	}
	else {
		ItemCount += Count;
	}
}

void ABagItem::DecItem(int32 Count) {
	if (GetLocalRole() < ROLE_Authority) {
		ServerDecItem(Count);
	}
	else {
		ItemCount -= Count;
	}
}

void ABagItem::SetItemOwner(AActor* player) {
	if (GetLocalRole() < ROLE_Authority) {
		//ItemBelongTo = player;
		ServerSetItemOwner(player);
	}
	else {
		ItemBelongTo = player;
	}
}

void ABagItem::SetEquipState(bool mystate) {
	if (GetLocalRole() < ROLE_Authority) {
		ServerSetEquipState(mystate);
	}
	else {
		ItemEquiped = mystate;
	}
}

void ABagItem::SetInSlotState(int32 mystate) {
	if (GetLocalRole() < ROLE_Authority) {
		ServerSetInSlotState(mystate);
	}
	else {
		ItemInSlot = mystate;
	}
}

void ABagItem::ServerAddItem_Implementation(int32 Count) {
	AddItem(Count);
}

void ABagItem::ServerDecItem_Implementation(int32 Count) {
	DecItem(Count);
}

void ABagItem::ServerSetEquipState_Implementation(bool mystate) {
	SetEquipState(mystate);
}

void ABagItem::ServerSetInSlotState_Implementation(int32 mystate) {
	SetInSlotState(mystate);
}

void ABagItem::ServerSetItemOwner_Implementation(AActor* player) {
	SetItemOwner(player);
}