// AYMonsterBase.cpp

#include "AYMonsterBase.h"
#include "MonsterAnimInstance.h"
#include "PreLoder.h"
#include "Kismet/KismetMathLibrary.h"
#include "Protobuf/Protocol.pb.h"

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

    GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
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
    //
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

void AAYMonsterBase::RepMonsterState(FVector pos, Protocol::ActorState state)
{
    MyLocation = GetActorLocation(); // ���� ��ġ ����
    //TargetLocation = pos;   // �����κ��� ���� ��ǥ ��ġ ����
    //LerpAlpha = 0.0f;

    SetActorLocation(pos);

    //CurrentRotation = GetActorQuat();   // ���� ȸ�� ����
    //TargetRotation = quat; // �����κ��� ���� ��ǥ ȸ�� ����
    //SlerpAlpha = 0.0f;

    FVector loc = MyLocation;
    loc.Z = 0.f;
    FVector targetLoc = TargetLocation;
    targetLoc.Z = 0.f;

    FVector dir = targetLoc - loc;
    dir.Normalize();

    SetActorRotation(FRotator(0.f, dir.Rotation().Yaw, 0.f));
    Anim->SetAnimState(ConvertAnimState(state));
}

void AAYMonsterBase::RepMonsterState(FVector pos, FVector targetPos, Protocol::ActorState state)
{
    MyLocation = GetActorLocation(); // ���� ��ġ ����
    CurLocation = pos;   // �����κ��� ���� ��ǥ ��ġ ����
    LerpAlpha = 0.0f;

    if (targetPos.Size() > 0)
    {
        TargetLocation = targetPos;
        CurrentRotation = GetActorQuat();   // ���� ȸ�� ����
        FRotator rotator = UKismetMathLibrary::FindLookAtRotation(MyLocation, TargetLocation);
        TargetRotation = rotator.Quaternion();
        SlerpAlpha = 0.0f;
        FVector pp = GetActorForwardVector();
    }

    Anim->SetAnimState(ConvertAnimState(state));
}

//
//
//void AAYMonsterBase::RepMonsterState(FVector pos, FVector Target, Protocol::ActorState state)
//{
//    CurrentLocation = pos;
//    TargetLocation = Target;
//    Anim->SetAnimState(ConvertAnimState(state));
//
//    FVector loc = CurrentLocation;
//    loc.Z = 0.f;
//    FVector targetLoc = TargetLocation;
//    targetLoc.Z = 0;
//
//    FVector dir = targetLoc - loc;
//    dir.Normalize();
//
//    SetActorRotation(FRotator(0.f, dir.Rotation().Yaw, 0.f));
//}

void AAYMonsterBase::Move(float DeltaTime)
{
    // ���� ����ġ�� �������� �ε巯�� �̵��� ����
    LerpAlpha += DeltaTime * 8.0f; // 2.0f�� ���� �ӵ� ���� ��

    // ���� ����ġ�� [0, 1] ������ Ŭ����
    LerpAlpha = FMath::Clamp(LerpAlpha, 0.0f, 1.0f);

    // ���� ������ ����� ���� ��ġ�� ��ǥ ��ġ�� �ε巴�� �̵���Ŵ
    FVector NewLocation = FMath::Lerp(MyLocation, CurLocation, LerpAlpha);
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

EAnimState AAYMonsterBase::ConvertAnimState(Protocol::ActorState state)
{
    switch (state)
    {
    case Protocol::IDlE:
        return EAnimState::Idle;
        break;
    case Protocol::ATTACK1:
        return EAnimState::Attack1;
        break;
    case Protocol::HIT:
        return EAnimState::Hit;
        break;
    case Protocol::MOVE:
        return EAnimState::Move;
        break;
    case Protocol::DEAD:
        return EAnimState::Dead;
        break;
    case Protocol::ActorState_INT_MIN_SENTINEL_DO_NOT_USE_:
    case Protocol::ActorState_INT_MAX_SENTINEL_DO_NOT_USE_:
        return EAnimState::Idle;
        break;
    }

    return EAnimState::Idle;

}

