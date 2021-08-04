// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemEffect.generated.h"

/**
 * 
 */


UCLASS()
class INVENTORYSYSTEM_API UItemEffect : public UObject
{
	GENERATED_BODY()
public:
	UItemEffect();

	UFUNCTION(BlueprintCallable)
	void ActivateEffect(AActor* otherActor=nullptr);

	UFUNCTION(BlueprintCallable)
	void RemoveEffect(AActor* otherActor = nullptr);

};
