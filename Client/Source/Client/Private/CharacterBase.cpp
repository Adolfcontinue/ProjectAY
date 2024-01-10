// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterBase::SetPlayerKey(int64 playerKey)
{
	PlayerKey = playerKey;
}

int64 ACharacterBase::GetPalyerKey()
{
	return PlayerKey;
}

void ACharacterBase::RepPlayerMove(FVector pos, FQuat quat)
{
	CurrentLocation = GetActorLocation(); // ���� ��ġ ����
	TargetLocation = pos;   // �����κ��� ���� ��ǥ ��ġ ����
	LerpAlpha = 0.0f;

	CurrentRotation = GetActorQuat();   // ���� ȸ�� ����
	TargetRotation = quat; // �����κ��� ���� ��ǥ ȸ�� ����
	SlerpAlpha = 0.0f;
}

