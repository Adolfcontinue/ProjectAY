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
        // 그로기 상태일 때는 대미지를 받지 않음
        return;
    }

    Health -= DamageAmount;
    Anim->SetAnimState(EAnimState::Hit);
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

void AAYMonsterBase::RepMonsterState(FVector pos, Protocol::ActorState state)
{
    MyLocation = GetActorLocation(); // 현재 위치 저장
    //TargetLocation = pos;   // 서버로부터 받은 목표 위치 설정
    //LerpAlpha = 0.0f;

    SetActorLocation(pos);

    //CurrentRotation = GetActorQuat();   // 현재 회전 저장
    //TargetRotation = quat; // 서버로부터 받은 목표 회전 설정
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
    MyLocation = GetActorLocation(); // 현재 위치 저장
    CurLocation = pos;   // 서버로부터 받은 목표 위치 설정
    LerpAlpha = 0.0f;

    if (targetPos.Size() > 0)
    {
        TargetLocation = targetPos;
        CurrentRotation = GetActorQuat();   // 현재 회전 저장
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
    // 보간 가중치를 증가시켜 부드러운 이동을 만듦
    LerpAlpha += DeltaTime * 8.0f; // 2.0f는 보간 속도 조절 값

    // 보간 가중치를 [0, 1] 범위로 클램프
    LerpAlpha = FMath::Clamp(LerpAlpha, 0.0f, 1.0f);

    // 선형 보간을 사용해 현재 위치를 목표 위치로 부드럽게 이동시킴
    FVector NewLocation = FMath::Lerp(MyLocation, CurLocation, LerpAlpha);
    SetActorLocation(NewLocation);
}

void AAYMonsterBase::Rotation(float DeltaTime)
{
    SlerpAlpha += DeltaTime * 5.0f; // 보간 속도 조절 값 (2.0f는 예시, 조절 필요)
    SlerpAlpha = FMath::Clamp(SlerpAlpha, 0.0f, 1.0f); // [0, 1] 범위로 클램프

    // 쿼터니언 Slerp를 사용해 현재 회전을 목표 회전으로 부드럽게 이동시킴
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

