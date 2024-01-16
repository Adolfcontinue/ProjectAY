// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PreLoder.h"
#include "../AYGameInstance.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
}

void UPlayerAnimInstance::NativeUpdateAnimation(float deltaSecond)
{
	Super::NativeUpdateAnimation(deltaSecond);
	auto pawn = TryGetPawnOwner();
	if (::IsValid(pawn))
	{
		auto character = Cast<ACharacter>(pawn);
		if (character)
			isInAir = character->GetMovementComponent()->IsFalling();
	}
}

void UPlayerAnimInstance::SetAnimState(EAnimState state)
{
	AnimState = state;    
}

EAnimState UPlayerAnimInstance::GetAnimState()
{
	return AnimState;
}

Protocol::PlayerState UPlayerAnimInstance::GetAnimStateProtobuf()
{
	switch (AnimState)
	{
	case EAnimState::Idle:	
		return Protocol::PlayerState::IDlE;
	case EAnimState::Attack1:		
		return Protocol::PlayerState::ATTACK1;
	case EAnimState::Move:
		return Protocol::PlayerState::MOVE;
	case EAnimState::Dead:
		return Protocol::PlayerState::DEAD;
		break;
	default:
		break;
	}

	return Protocol::PlayerState::IDlE;
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	OnAttack1_EndCheck.Broadcast();
	LOG_SCREEN(FColor::Blue, "AnimNotify_AttackEnd");
}

void UPlayerAnimInstance::AnimNotify_AttackEndCheck()
{
	OnAttack2_EndCheck.Broadcast();
	LOG_SCREEN(FColor::Blue, "AnimNotify_AttackEndCheck");
}

void UPlayerAnimInstance::AnimNotify_PlayerAttack()
{
	OnAttackHitCheck.Broadcast();
	LOG_SCREEN(FColor::Red, "AnimNotify_PlayerAttack");
}
