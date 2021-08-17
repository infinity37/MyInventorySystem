// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BackPackComponent.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBackPackComponent* myBackPack;

	UFUNCTION(BlueprintCallable)
		int32 GetItemCountById(int TypeId);

	UFUNCTION(BlueprintCallable)
		int32 GetWeaponDamageById(int TypeId);

};
