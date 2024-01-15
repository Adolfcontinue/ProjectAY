// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBeholder.h"

AMonsterBeholder::AMonsterBeholder()
{
	MonsterKey = MonsterType::Beholder;

    ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalmesh(TEXT("/Game/Asset/RPGMonsterWave2PBR/Mesh/Beholder/Beholder_SK.Beholder_SK"));
    if (skeletalmesh.Succeeded())
        GetMesh()->SetSkeletalMesh(skeletalmesh.Object);

    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

    ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Game/Blueprint/Character/BeholderAnimBP.BeholderAnimBP_C"));
    if (anim.Succeeded())
        GetMesh()->SetAnimInstanceClass(anim.Class);

    GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
}


