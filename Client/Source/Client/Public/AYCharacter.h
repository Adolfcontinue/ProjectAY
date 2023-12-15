// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "GameFramework/Character.h"
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

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

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

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted);

private:
	eControlType CurrentControlType = eControlType::Type1;
	FVector DirectionToMove = FVector::ZeroVector;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY()
	class UDarkNightAnimInstance* _Anim;
};
