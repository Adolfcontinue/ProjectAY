// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorWeapon.h"

// Sets default values
AActorWeapon::AActorWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AActorWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActorWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

