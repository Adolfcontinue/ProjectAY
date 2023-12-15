// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkNightAnimInstance.h"
#include "PreLoder.h"

UDarkNightAnimInstance::UDarkNightAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	isInAir = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> combo_attack(TEXT("/Game/Blueprint/Character/GreatSwordComboAttack_Montage.GreatSwordComboAttack_Montage"));
	if (combo_attack.Succeeded())
		ComboAttackMontage = combo_attack.Object;
}

void UDarkNightAnimInstance::NativeUpdateAnimation(float deltaSecond)
{
	Super::NativeUpdateAnimation(deltaSecond);

	auto pawn = TryGetPawnOwner();
	if (::IsValid(pawn))
	{
		CurrentPawnSpeed = pawn->GetVelocity().Size();
		auto character = Cast<ACharacter>(pawn);
		if (character)
			isInAir = character->GetMovementComponent()->IsFalling();
	}
}

void UDarkNightAnimInstance::PlayComboAttackMontage()
{
	Montage_Play(ComboAttackMontage,0.51f);
}

void UDarkNightAnimInstance::JumpToAttackMontageSection(int32 newSecion)
{
	LOG("JumpToAttackMontageSection BEGIN");
	CHECK(Montage_IsPlaying(ComboAttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(newSecion), ComboAttackMontage);
	LOG("JumpToAttackMontageSection END");
}

void UDarkNightAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UDarkNightAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UDarkNightAnimInstance::GetAttackMontageSectionName(int32 section)
{
	CHECK(FMath::IsWithinInclusive<int32>(section, 1, 3), NAME_None);
	return FName(*FString::Printf(TEXT("ComboAttack%d"), section));
}
