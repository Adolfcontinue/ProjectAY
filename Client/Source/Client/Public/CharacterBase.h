// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class CLIENT_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void SetPlayerKey(int64 PlayerKey);
	int64 GetPalyerKey();

public:
	void RepPlayerMove(FVector pos, FQuat quat);

protected:
	int64 PlayerKey;
	FVector CurrentLocation;
	FVector TargetLocation;
	float LerpAlpha;
	FQuat CurrentRotation;
	FQuat TargetRotation;
	float SlerpAlpha;

};
