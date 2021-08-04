// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemEffect.h"
#include "ItemInfoTable.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "BagItem.generated.h"


UCLASS()
class INVENTORYSYSTEM_API ABagItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABagItem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ItemTypeId;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		int32 ItemCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UItemInfo* ItemInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		AActor* ItemBelongTo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		bool ItemEquiped;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		int32 ItemInSlot;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void EquipItem();

	UFUNCTION(BlueprintCallable)
	virtual void UnEquipItem();

	UFUNCTION(BlueprintCallable)
	virtual bool IsEquiped();

	UFUNCTION(BlueprintCallable)
	virtual void UseItem();

	UFUNCTION(BlueprintCallable)
		void AddItem(int32 Count);

	UFUNCTION(BlueprintCallable)
		void DecItem(int32 Count);

	UFUNCTION(BlueprintCallable)
		void SetEquipState(bool mystate);

	UFUNCTION(BlueprintCallable)
		void SetItemOwner(AActor* player);

	UFUNCTION(Server, Reliable)
		void ServerSetItemOwner(AActor* player);

	UFUNCTION(Server, Reliable)
		void ServerAddItem(int32 Count);

	UFUNCTION(Server, Reliable)
		void ServerDecItem(int32 Count);

	UFUNCTION(Server, Reliable)
		void ServerSetEquipState(bool mystate);

	UFUNCTION(BlueprintCallable)
		void SetInSlotState(int32 mystate);

	UFUNCTION(Server, Reliable)
		void ServerSetInSlotState(int32 mystate);


	int32 GetWeight();
	int32 GetMaxCount();
	FString GetName();
	FString GetDescription();
};
