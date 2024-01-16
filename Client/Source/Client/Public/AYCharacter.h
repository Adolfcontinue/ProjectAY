// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "GameFramework/Character.h"
#include "Protobuf/Enum.pb.h"
#include "Define.h"
#include "AYCharacter.generated.h"

UCLASS()
class CLIENT_API AAYCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAYCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class eControlType
	{
		Type1,
		Type2
	};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



private:
	void UpDown(float axisValue);
	void LeftRight(float axisValue);
	void Turn(float axisValue);
	void LookUp(float axisValue);

	void SetControl(eControlType type);
	void ControlType1();
	void ContrilType2();
	void TickMove();
	void ComboAttack();

	void AttackEndCheck();
	void AttackCheck();
	void AnimSync();
	void SetAnimState(EAnimState animstate);

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	//USkeletalMeshComponent* Weapon;
	UStaticMeshComponent* Weapon;

private:
	eControlType CurrentControlType = eControlType::Type1;
	FVector DirectionToMove = FVector::ZeroVector;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY()
	class UPlayerAnimInstance* _Anim;

	float SyncTimer;
};
