// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBlackKnight.h"
#include "PreLoder.h"

AMonsterBlackKnight::AMonsterBlackKnight()
{
    MonsterKey = MonsterType::BlackKnight;

    ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalmesh(TEXT("/Game/Asset/RPGMonsterWave2PBR/Mesh/BlackKnight/BlackKnight_SK.BlackKnight_SK"));
    if (skeletalmesh.Succeeded())
        GetMesh()->SetSkeletalMesh(skeletalmesh.Object);

    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Game/Blueprint/Character/BlackKnightAnimBP.BlackKnightAnimBP_C"));
    if (anim.Succeeded())
        GetMesh()->SetAnimInstanceClass(anim.Class);

    GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
}

void AMonsterBlackKnight::BeginPlay()
{
    Super::BeginPlay();
    FVector v = GetActorForwardVector();
    LOG("BlackKnight", v.X, v.Y, v.Z);
}

void AMonsterBlackKnight::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMonsterBlackKnight::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

