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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<ABagItem*> WeaponSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<ABagItem*> AttachmentSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<ABagItem*> AvatarSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRepNormalSpaceDebug)
		TMap<int32,ABagItem*> NormalSpace;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
		APlayerController* Owner;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	UFUNCTION()
	void OnRepNormalSpaceDebug();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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
	UFUNCTION(BlueprintCallable)
		void DropItem(int32 ItemTypeId, int32 Count);

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void ServerDropItem(int32 ItemTypeId, int32 Count);
		void ServerDropItem_Implementation(int32 ItemTypeId, int32 Count);

	UFUNCTION(Client, Reliable, BlueprintCallable)
		void ClientDropItem(int32 ItemTypeId, int32 Count);
		void ClientDropItem_Implementation(int32 ItemTypeId, int32 Count);

	UFUNCTION(BlueprintCallable)
		void UseItem(int32 ItemTypeId);

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void ServerUseItem(int32 ItemTypeId);
		void ServerUseItem_Implementation(int32 ItemTypeId);

	UFUNCTION(Client, Reliable, BlueprintCallable)
		void ClientUseItem(int32 ItemTypeId);
		void ClientUseItem_Implementation(int32 ItemTypeId);

	UFUNCTION(BlueprintCallable)
		void AddToWeaponSlot(int32 ItemTypeId, int32 pos);

	UFUNCTION(BlueprintCallable)
		bool AddToAttachmentSlot(int32 ItemTypeId, int32 pos);

	UFUNCTION(BlueprintCallable)
		bool AddToAvatarSlot(int32 ItemTypeId, int32 pos);

	UFUNCTION(BlueprintCallable)
		void RemoveFromWeaponSlot(int32 pos);

	UFUNCTION(BlueprintCallable)
		void RemoveFromAttachmentSlot(int32 pos);

	UFUNCTION(BlueprintCallable)
		void RemoveFromAvatarSlot(int32 pos);
};
