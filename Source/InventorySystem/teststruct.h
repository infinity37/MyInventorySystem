#pragma once

#include "CoreMinimal.h"
#include "ItemEffect.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "teststruct.generated.h"


UENUM(BlueprintType)
enum class AttriName : uint8
{
	Damage,
	DamageMul,
	Energy,
	EnergyMul,
	Health,
	TrueDamage,
	TrueEnergy,
	AmmoCount,
};

UENUM(BlueprintType)
enum class EffectAttrs : uint8 {
	Health, 
	Speed, 
	Damage, 
	Energy, 
	AmmoCount,
};

UENUM(BlueprintType)
enum class CalcType : uint8 {
	CAdd, 
	CMul, 
	CSet,
};

USTRUCT(BlueprintType)
struct FEffectInfo {
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		CalcType EffectCalc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AttriName TargetAttr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float calcValue;
};

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

public:
	FInventoryItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemTypeId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemMaxCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FEffectInfo> ItemEffects;
};

USTRUCT(BlueprintType) 
struct FWeaponInfo : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

public:
	FWeaponInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemTypeId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxAmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int32> AttachmentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* WeaponMesh;
};