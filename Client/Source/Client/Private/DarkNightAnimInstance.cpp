// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkNightAnimInstance.h"

UDarkNightAnimInstance::UDarkNightAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	isInAir = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> combo_attack(TEXT("/Game/Blueprint/Character/UE4_Mannequin_Skeleton_Montage.UE4_Mannequin_Skeleton_Montage"));
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
	Montage_Play(ComboAttackMontage, 1.0f);
}
