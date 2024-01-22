// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
}

void UMonsterAnimInstance::NativeUpdateAnimation(float deltaSecond)
{
	Super::NativeUpdateAnimation(deltaSecond);
}

void UMonsterAnimInstance::SetAnimState(EAnimState state)
{
	AnimState = state;
}

void UMonsterAnimInstance::AnimNotify_monsterhit()
{
	//todo
	SetAnimState(EAnimState::Idle);
}

void UMonsterAnimInstance::AnimNotify_monsterattack()
{
	//todo
	SetAnimState(EAnimState::Idle);
}

