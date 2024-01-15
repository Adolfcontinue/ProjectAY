// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterChest.h"

AMonsterChest::AMonsterChest()
{
    MonsterKey = MonsterType::Chest;
    ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalmesh(TEXT("/Game/Asset/RPGMonsterWave2PBR/Mesh/ChestMonster/ChestMonster_SK.ChestMonster_SK"));
    if (skeletalmesh.Succeeded())
        GetMesh()->SetSkeletalMesh(skeletalmesh.Object);

    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprint/Character/ChestAnimBP.ChestAnimBP'_C"));
    if (anim.Succeeded())
        GetMesh()->SetAnimInstanceClass(anim.Class);

    GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
}
