// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "Animation/AnimInstance.h"
#include "Define.h"
#include "GreatSwordAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API UGreatSwordAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UGreatSwordAnimInstance();
	virtual void NativeUpdateAnimation(float deltaSecond) override;


private:
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EAnimState AnimState;
};
