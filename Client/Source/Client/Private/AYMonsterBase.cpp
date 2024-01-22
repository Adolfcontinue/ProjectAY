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
    //
    if (TargetLocation.Size() > 0)
        Move(DeltaTime);

    if (TargetRotation.Size() > 0)
        Rotation(DeltaTime);
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

    FQuat f = GetActorQuat();
    FRotator r = GetActorRotation();

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

void AAYMonsterBase::RepMonsterState(FVector pos, FQuat quat)
{
    CurrentLocation = GetActorLocation(); // ���� ��ġ ����
    TargetLocation = pos;   // �����κ��� ���� ��ǥ ��ġ ����
    LerpAlpha = 0.0f;

    CurrentRotation = GetActorQuat();   // ���� ȸ�� ����
    TargetRotation = quat; // �����κ��� ���� ��ǥ ȸ�� ����
    SlerpAlpha = 0.0f;
}

void AAYMonsterBase::Move(float DeltaTime)
{
    // ���� ����ġ�� �������� �ε巯�� �̵��� ����
    LerpAlpha += DeltaTime * 8.0f; // 2.0f�� ���� �ӵ� ���� ��

    // ���� ����ġ�� [0, 1] ������ Ŭ����
    LerpAlpha = FMath::Clamp(LerpAlpha, 0.0f, 1.0f);

    // ���� ������ ����� ���� ��ġ�� ��ǥ ��ġ�� �ε巴�� �̵���Ŵ
    FVector NewLocation = FMath::Lerp(CurrentLocation, TargetLocation, LerpAlpha);
    SetActorLocation(NewLocation);
}

void AAYMonsterBase::Rotation(float DeltaTime)
{
    SlerpAlpha += DeltaTime * 5.0f; // ���� �ӵ� ���� �� (2.0f�� ����, ���� �ʿ�)
    SlerpAlpha = FMath::Clamp(SlerpAlpha, 0.0f, 1.0f); // [0, 1] ������ Ŭ����

    // ���ʹϾ� Slerp�� ����� ���� ȸ���� ��ǥ ȸ������ �ε巴�� �̵���Ŵ
    FQuat NewRotation = FQuat::Slerp(CurrentRotation, TargetRotation, SlerpAlpha);
    SetActorRotation(NewRotation);
}

