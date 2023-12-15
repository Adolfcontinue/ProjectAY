// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSwordAnimInstance.h"

UGreatSwordAnimInstance::UGreatSwordAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	isInAir = false;

	//static ConstructorHelpers::FObjectFinder<UAnimMontage> combo_attack(TEXT("/Game/Blueprint/Character/UE4_Mannequin_Skeleton_Montage.UE4_Mannequin_Skeleton_Montage"));
	//if (combo_attack.Succeeded())
	//	ComboAttackMontage = combo_attack.Object;
}

void UGreatSwordAnimInstance::NativeUpdateAnimation(float deltaSecond)
{
	//Super::NativeUpdateAnimation(deltaSecond);

	//auto pawn = TryGetPawnOwner();
	//if (::IsValid(pawn))
	//{
	//	CurrentPawnSpeed = pawn->GetVelocity().Size();
	//	auto character = Cast<ACharacter>(pawn);
	//	if (character)
	//		isInAir = character->GetMovementComponent()->IsFalling();
	//}
}

void UGreatSwordAnimInstance::PlayComboAttackMontage()
{
	Montage_Play(ComboAttackMontage, 1.0f);
}
