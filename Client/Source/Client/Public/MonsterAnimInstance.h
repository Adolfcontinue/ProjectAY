// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "Animation/AnimInstance.h"
#include "Define.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnMonsterAttackDelegate);

UCLASS()
class CLIENT_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterAnimInstance();
	virtual void NativeUpdateAnimation(float deltaSecond) override;

	FOnMonsterAttackDelegate MonstertAttackDelegate;

public:
	void SetAnimState(EAnimState state);
	void AddAnimState(EAnimState state);

private:
	UFUNCTION()
	void AnimNotify_monsterhit();

	UFUNCTION()
	void AnimNotify_monsterattack();

private:
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EAnimState AnimState;

	TQueue<EAnimState> AnimStateQueue;
};
