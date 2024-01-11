// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "Define.h"
#include "Protobuf/Enum.pb.h"
#include "OtherCharacter.generated.h"

UCLASS()
class CLIENT_API AOtherCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOtherCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(float DeltaTime);
	void Rotation(float DeltaTime);

	void SetAnimState(EAnimState state);
	void SetAnimState(Protocol::PlayerState state);

private:
	EAnimState AnimState;

private:
	UPROPERTY()
	class UPlayerAnimInstance* Anim;
};
