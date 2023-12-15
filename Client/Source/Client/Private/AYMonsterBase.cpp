// AYMonsterBase.cpp

#include "AYMonsterBase.h"

// Sets default values
AAYMonsterBase::AAYMonsterBase()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Initialize default values
    MaxHealth = 100.0f;
    Health = MaxHealth;
    AttackPower = 10.0f;
    bIsStunned = false;
}

// Called when the game starts or when spawned
void AAYMonsterBase::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AAYMonsterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAYMonsterBase::TakeDamage(float DamageAmount)
{
    if (bIsStunned)
    {
        // 그로기 상태일 때는 대미지를 받지 않음
        return;
    }

    Health -= DamageAmount;

    if (Health <= 0.0f)
    {
        // 몬스터가 사망한 경우 처리
        // 예를 들어, 애니메이션 재생, 아이템 드롭 등
        Destroy();
    }
}

void AAYMonsterBase::ApplyStun(float StunDuration)
{
    bIsStunned = true;

    // 일정 시간이 지난 후 그로기 상태 해제
    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, [this]() {
        bIsStunned = false;
        }, StunDuration, false);
}

