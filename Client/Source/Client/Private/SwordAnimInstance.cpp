// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordAnimInstance.h"

USwordAnimInstance::USwordAnimInstance()
{
}

void USwordAnimInstance::NativeUpdateAnimation(float deltaSecond)
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
