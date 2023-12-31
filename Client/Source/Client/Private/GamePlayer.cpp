// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayer.h"

// Sets default values
AGamePlayer::AGamePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGamePlayer::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGamePlayer::SetPlayerKey(uint64 userKey)
{
	_PlayerKey = userKey;
}

uint64 AGamePlayer::GetPlayerKey()
{
	return _PlayerKey;
}



