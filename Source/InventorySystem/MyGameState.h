// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "teststruct.h"
#include "ItemInfoTable.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMyGameState();

	UFUNCTION(BlueprintCallable)
	class UItemInfoTable* GetItemInfoTable() const;

protected:
	//UPROPERTY(EditDefaultsOnly)
	UPROPERTY(VisibleAnywhere)
		UDataTable* ItemDataTable;

	UPROPERTY(VisibleAnywhere)
		UDataTable* WeaponTable;

	//UPROPERTY(EditDefaultsOnly)
	UPROPERTY(VisibleAnywhere)
		UItemInfoTable* ItemInfoTable;
};
