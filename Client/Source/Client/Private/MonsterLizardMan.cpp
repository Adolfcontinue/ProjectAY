// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterLizardMan.h"

AMonsterLizardMan::AMonsterLizardMan()
{
    MonsterKey = MonsterType::Lizard;
    ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalmesh(TEXT("/Game/Asset/RPGMonsterWave2PBR/Mesh/LizardWarrior/LizardWarrior_SK.LizardWarrior_SK"));
    if (skeletalmesh.Succeeded())
        GetMesh()->SetSkeletalMesh(skeletalmesh.Object);

    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Game/Blueprint/Character/LizardAnimBP.LizardAnimBP_C"));
    if (anim.Succeeded())
        GetMesh()->SetAnimInstanceClass(anim.Class);

    GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -70.f));
}
