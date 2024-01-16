// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "Animation/AnimInstance.h"
#include "Define.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterAnimInstance();
	virtual void NativeUpdateAnimation(float deltaSecond) override;

public:
	void SetAnimState(EAnimState state);

private:
	UFUNCTION()
	void AnimNotify_monsterhit();

private:
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EAnimState AnimState;

};
