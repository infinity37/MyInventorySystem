// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BagItem.h"
#include "Net/UnrealNetwork.h"
#include "Components/ActorComponent.h"
#include "BackPackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UBackPackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBackPackComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		int32 CurrentWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 BackPackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 EquipedSlotId;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RefreshUI)
		TArray<ABagItem*> WeaponSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RefreshUI)
		TArray<ABagItem*> AttachmentSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<ABagItem*> AvatarSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_RefreshUI)
		TArray<ABagItem*> NormalSpace;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
		APlayerController* Owner;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UFUNCTION()
	void OnRep_RefreshUI();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	AActor* GetItemById(int32 TypeId);

	UFUNCTION(BlueprintCallable)
		bool CanAddItem(int32 ItemTypeId, int32 Count);

	UFUNCTION(BlueprintCallable)
		void AddItem(int32 ItemTypeId, int32 Count, AActor* otherActor);

	void AddAmmoToNormalSpace(int32 ItemTypeId, int32 Count, AActor* otherActor);

protected:
	UFUNCTION(BlueprintCallable)
		bool IsNewItem(int32 ItemTypeId);

	UFUNCTION(BlueprintCallable)
		void AddNewItem(int32 ItemTypeId, int32 Count, AActor* otherActor);

	UFUNCTION(BlueprintCallable)
		void AddOldItem(int32 ItemTypeId, int32 Count);

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
		void DropItem(int32 ItemTypeId, int32 Count);
		void DropItem_Implementation(int32 ItemTypeId, int32 Count);

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void UseItem(int32 ItemTypeId);
		void UseItem_Implementation(int32 ItemTypeId);

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void AddToWeaponSlot(int32 ItemTypeId, int32 pos);

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void AddToAttachmentSlot(int32 ItemTypeId, int32 pos);

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void RemoveFromWeaponSlot(int32 pos);

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void RemoveFromAttachmentSlot(int32 pos);

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void EquipWeapon(int WeaponId);
		void EquipWeapon_Implementation(int WeaponId);

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void UnEquipWeapon(int WeaponId);
		void UnEquipWeapon_Implementation(int WeaponId);

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void ReloadWeapon(int WeaponId);
		void ReloadWeapon_Implementation(int WeaponId);
	
	UFUNCTION(Server, Reliable, BlueprintCallable)
		void ChangeEquipedSlot();
		void ChangeEquipedSlot_Implementation();


	UFUNCTION(BlueprintCallable)
		void RemoveFromAvatarSlot(int32 pos);
	UFUNCTION(BlueprintCallable)
		bool AddToAvatarSlot(int32 ItemTypeId, int32 pos);
};
