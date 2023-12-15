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
        // �׷α� ������ ���� ������� ���� ����
        return;
    }

    Health -= DamageAmount;

    if (Health <= 0.0f)
    {
        // ���Ͱ� ����� ��� ó��
        // ���� ���, �ִϸ��̼� ���, ������ ��� ��
        Destroy();
    }
}

void AAYMonsterBase::ApplyStun(float StunDuration)
{
    bIsStunned = true;

    // ���� �ð��� ���� �� �׷α� ���� ����
    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, [this]() {
        bIsStunned = false;
        }, StunDuration, false);
}

