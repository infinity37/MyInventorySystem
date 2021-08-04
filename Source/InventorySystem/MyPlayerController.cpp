// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Net/UnrealNetwork.h"

AMyPlayerController::AMyPlayerController() {
	myBackPack = CreateDefaultSubobject<UBackPackComponent>(TEXT("myBackPack"));
	myBackPack->Owner = this;
	//myBackPack->SetNetAddressable();
	myBackPack->SetIsReplicated(true);
}

int32 AMyPlayerController::GetItemCountById(int TypeId) {
	if (myBackPack->NormalSpace.Contains(TypeId)) {
		return (myBackPack->NormalSpace[TypeId])->ItemCount;
	}
	else {
		return 0;
	}
}
