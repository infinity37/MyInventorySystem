// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemEffect.h"
#include "teststruct.h"
#include "UObject/NoExportTypes.h"
#include "ItemInfoTable.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UItemInfo : public UObject {
	GENERATED_BODY()

public:
	UItemInfo();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 ItemTypeId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 ItemWeight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 ItemMaxCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString ItemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ItemIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FEffectInfo> Effects;

};

UCLASS()
class INVENTORYSYSTEM_API UItemInfoTable : public UObject
{
	GENERATED_BODY()
public:
	UItemInfoTable();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<int32, UItemInfo*> infotable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<int32, FWeaponInfo> weapontable;

	UFUNCTION(BlueprintCallable)
	UItemInfo* GetItemInfoById(int32 Id);

	UFUNCTION(BlueprintCallable)
		FWeaponInfo GetWeaponInfoById(int32 Id);
};
