// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "teststruct.h"
#include "InventorySystemCharacter.generated.h"




UCLASS(config=Game)
class AInventorySystemCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AInventorySystemCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<AActor*> PickUpList;

	UFUNCTION(BlueprintCallable)
		void SetCurrentWeapon(int32 cw);

	UFUNCTION(BlueprintCallable)
		int32 GetCurrentWeapon();

	UFUNCTION(Server, Reliable)
		void GenerateNewPickUp(int32 TypeId, int32 Count);


	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CurrentWeaponDebug)
		int32 CurrentWeaponId;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CurrentWeaponDebug)
	//	AActor* CurrentWeaponId;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		int32 Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		float DamageMul;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		int32 Energy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		int32 MaxEnergy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		float EnergyMul;

public:
	UFUNCTION(BlueprintCallable)
		void SetIntAttribute(AttriName AttName, int32 value);

	UFUNCTION(BlueprintCallable)
		void SetFloatAttribute(AttriName AttName, float value);

	UFUNCTION(BlueprintCallable)
		int32 GetIntAttribute(AttriName AttName);

	UFUNCTION(BlueprintCallable)
		float GetFloatAttribute(AttriName AttName);

protected:
	UFUNCTION(Server, Reliable)
		void ServerSetIntAttribute(AttriName AttName, int32 value);

	UFUNCTION(Server, Reliable)
		void ServerSetFloatAttribute(AttriName AttName, float value);

	UFUNCTION(Server, Reliable)
		void ServerSetCurrentWeapon(int32 cw);

	UFUNCTION()
		void OnRep_CurrentWeaponDebug();

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

