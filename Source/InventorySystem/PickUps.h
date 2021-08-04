// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "PickUps.generated.h"

UCLASS()
class INVENTORYSYSTEM_API APickUps : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUps();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
		int32 ItemTypeId;

	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CollisionComp;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 ItemCount;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	UFUNCTION(BlueprintCallable)
		void SetItem(int32 Id, int32 Count);

	UFUNCTION(Server, Reliable)
		void ServerSetItem(int32 Id, int32 Count);

};
