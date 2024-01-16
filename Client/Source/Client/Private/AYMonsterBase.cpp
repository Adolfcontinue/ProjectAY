// AYMonsterBase.cpp

#include "AYMonsterBase.h"
#include "MonsterAnimInstance.h"
#include "PreLoder.h"

// Sets default values
AAYMonsterBase::AAYMonsterBase()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Initialize default values
    MaxHealth = 500.0f;
    Health = MaxHealth;
    AttackPower = 10.0f;
    bIsStunned = false;

    ActorKey = -1;
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
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

void AAYMonsterBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    Anim = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
}

void AAYMonsterBase::SetActorKey(uint64 key)
{
    ActorKey = key;
}

uint64 AAYMonsterBase::GetActorKey()
{
    return ActorKey;
}

void AAYMonsterBase::TakeDamage(float DamageAmount)
{
    if (bIsStunned)
    {
        // �׷α� ������ ���� ������� ���� ����
        return;
    }

    Health -= DamageAmount;

    LOG("MONSTER TAKE DAMAGE CALL");

    //todo
    Anim->SetAnimState(EAnimState::Hit);

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

