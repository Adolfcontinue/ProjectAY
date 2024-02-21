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
	if (AnimState == EAnimState::Idle)
		AnimState = state;
	else
		AnimStateQueue.Enqueue(state);
}

void UMonsterAnimInstance::AddAnimState(EAnimState state)
{
	AnimStateQueue.Enqueue(state);
}

void UMonsterAnimInstance::AnimNotify_monsterhit()
{
	//todo`
	//SetAnimState(EAnimState::Idle);
	EAnimState outState = EAnimState::Idle;
	if (!AnimStateQueue.IsEmpty())
		AnimStateQueue.Dequeue(outState);

	AnimState = outState;
}

void UMonsterAnimInstance::AnimNotify_monsterattack()
{
	//todo
	EAnimState outState = EAnimState::Idle;
	if (!AnimStateQueue.IsEmpty())
		AnimStateQueue.Dequeue(outState);

	AnimState = outState;
}

