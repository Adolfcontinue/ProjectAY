// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "Animation/AnimInstance.h"
#include "DarkNightAnimInstance.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);


UCLASS()
class CLIENT_API UDarkNightAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UDarkNightAnimInstance();
	virtual void NativeUpdateAnimation(float deltaSecond) override;

	void PlayComboAttackMontage();
	void JumpToAttackMontageSection(int32 newSecion);

public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;

private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	FName GetAttackMontageSectionName(int32 section);

private:
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category=Pawn, Meta=(AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(Editanywhere, BlueprintReadOnly, Category=Pawn, Meta=(AllowPrivateAccess = true))
	bool isInAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ComboAttackMontage;
};
