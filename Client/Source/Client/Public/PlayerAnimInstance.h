// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "Animation/AnimInstance.h"
#include "Define.h"
#include "Protobuf/Enum.pb.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnAttack1EndkDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttack2EndkDelegate);


UCLASS()
class CLIENT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	FOnAttack1EndkDelegate OnAttack1_EndCheck;
	FOnAttack2EndkDelegate OnAttack2_EndCheck;

public:
	UPlayerAnimInstance();
	virtual void NativeUpdateAnimation(float deltaSecond) override;
	void SetAnimState(EAnimState state);
	EAnimState GetAnimState();
	Protocol::PlayerState GetAnimStateProtobuf();


private:
	UFUNCTION()
	void AnimNotify_AttackEnd();
	UFUNCTION()
	void AnimNotify_AttackEndCheck();

private:
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EAnimState AnimState;

	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool isInAir;

};
