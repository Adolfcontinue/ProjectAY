// AYMonsterBase.cpp

#include "AYMonsterBase.h"
#include "MonsterAnimInstance.h"
#include "PreLoder.h"
#include "Kismet/KismetMathLibrary.h"
#include "MonsterAIController.h"
#include "Protobuf/Protocol.pb.h"
#include "PlayerStatComponent.h"
#include "Components/WidgetComponent.h"
#include "CharacterWidget.h"
#include "../AYGameInstance.h"

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

    AIControllerClass = AMonsterAIController::StaticClass();

    Stat = CreateDefaultSubobject<UPlayerStatComponent>(TEXT("MONSTERSTAT"));

    HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
    HPBar->SetupAttachment(GetMesh());
    HPBar->SetRelativeLocation(FVector(0.0f, 10.0f, 180.f));
    HPBar->SetWidgetSpace(EWidgetSpace::Screen);
    static ConstructorHelpers::FClassFinder<UCharacterWidget> UI_HUD(TEXT("/Game/Blueprint/Widget/UI_HPBar.UI_HPBar_C"));
    if (UI_HUD.Succeeded())
    {
        HPBar->SetWidgetClass(UI_HUD.Class);
        HPBar->SetDrawSize(FVector2D(150.f, 50.f));
    }
}

// Called when the game starts or when spawned
void AAYMonsterBase::BeginPlay()
{
    Super::BeginPlay();

    AMonsterAIController* AIController = GetWorld()->SpawnActor<AMonsterAIController>();

    if (AIController)
        AIController->Possess(this);

    auto hpWidget = Cast<UCharacterWidget>(HPBar->GetUserWidgetObject());
    if (hpWidget != nullptr)
    {
        hpWidget->BindCharacterStat(Stat);
    }
}

// Called every frame
void AAYMonsterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //

    //if (CurLocation.Size() > 0)
    //{
    //    Move(DeltaTime);
    //    Anim->SetAnimState(EAnimState::Move);
    //}
    //if (MoveDir.Size() > 0)
    //{
    //    SetActorLocation(MyLocation + MoveDir);
    //    Anim->SetAnimState(EAnimState::Move);
    //    MyLocation = GetActorLocation(); // ���� ��ġ ����
    //} 
    /*if (CurLocation.Size() > 0)
        Move(DeltaTime);*/

    if (TargetRotation.Size() > 0)
        Rotation(DeltaTime);
}

void AAYMonsterBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    Anim = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());

    Anim->OnMonsterAttack.AddUObject(this, &AAYMonsterBase::AttackCheck);

}

void AAYMonsterBase::SetActorKey(uint64 key)
{
    ActorKey = key;
}

uint64 AAYMonsterBase::GetActorKey()
{
    return ActorKey;
}

void AAYMonsterBase::SetMonseterAsset()
{
    //todo
   /* switch (MonsterKey)
    {
    case Beholder:
    {
        USkeletalMesh* mesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/Asset/RPGMonsterWave2PBR/Mesh/Beholder/Beholder_SK.Beholder_SK'"));
        GetMesh()->SetSkeletalMesh(mesh);
    }
        break;
    case BlackKnight:
    {

    }
        break;
    case Chest:
    {

    }
        break;
    case Crab:
    {

    }
        break;
    case Demon:
    {

    }
        break;
    case Lizard:
    {

    }
        break;
    default:
        break;
    }*/
}

void AAYMonsterBase::TakeDamage(float DamageAmount)
{
    if (bIsStunned)
    {
        // �׷α� ������ ���� ������� ���� ����
        return;
    }

    Stat->TakeDamage(DamageAmount);

    //Health -= DamageAmount;

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

void AAYMonsterBase::RepMonsterState(FVector pos, FVector targetPos, Protocol::ActorState state)
{
    MyLocation = GetActorLocation(); // ���� ��ġ ����
    //SetActorLocation(pos);
    CurLocation = pos;   // �����κ��� ���� ��ǥ ��ġ ����
    LerpAlpha = 0.0f;
    
    AMonsterAIController* controller = Cast<AMonsterAIController>(GetController());
    controller->MoveToLocation(pos);
    
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

void AAYMonsterBase::Move(float DeltaTime)
{
    // ���� ����ġ�� �������� �ε巯�� �̵��� ����
    LerpAlpha += DeltaTime;// *20.0f; // 2.0f�� ���� �ӵ� ���� ��

    // ���� ����ġ�� [0, 1] ������ Ŭ����
    LerpAlpha = FMath::Clamp(LerpAlpha, 0.0f, 1.0f);

    // ���� ������ ����� ���� ��ġ�� ��ǥ ��ġ�� �ε巴�� �̵���Ŵ
    FVector NewLocation = FMath::Lerp(MyLocation, CurLocation, LerpAlpha);
    SetActorLocation(CurLocation);
}

void AAYMonsterBase::Rotation(float DeltaTime)
{
    SlerpAlpha += DeltaTime * 5.0f; // ���� �ӵ� ���� �� (2.0f�� ����, ���� �ʿ�)
    SlerpAlpha = FMath::Clamp(SlerpAlpha, 0.0f, 1.0f); // [0, 1] ������ Ŭ����

    // ���ʹϾ� Slerp�� ����� ���� ȸ���� ��ǥ ȸ������ �ε巴�� �̵���Ŵ
    FQuat NewRotation = FQuat::Slerp(CurrentRotation, TargetRotation, SlerpAlpha);
    SetActorRotation(NewRotation);
}

void AAYMonsterBase::AttackCheck()
{
    //monster attack
    FHitResult hitResult;
    FCollisionQueryParams params(NAME_None, false, this);
    bool bResult = GetWorld()->SweepSingleByChannel(
        hitResult,
        GetActorLocation(),
        GetActorLocation() + GetActorForwardVector() * 200.f,
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel4,
        FCollisionShape::MakeSphere(50.f),
        params
    );

    if (bResult)
    {
        if (IsValid(hitResult.GetActor()))
        {
            auto actor = hitResult.GetActor();

            Protocol::C2P_RequestMonsterAttack sendPacket;
            sendPacket.set_attacker(GetActorKey());
            sendPacket.set_damageamout(Stat->GetAttack());

            
            UAYGameInstance* inst = Cast<UAYGameInstance>(GetGameInstance());
            if (IsValid(inst))
                inst->Send(sendPacket, (uint16)(EPacket_C2P_Protocol::C2P_RequestMonsterAttack));

            //REPORT SERVER
            //LOG("PLAYER ATTACK CHECK");

            //FVector l = victim->GetActorLocation();
            //FVector l2 = GetActorLocation();

            
        }
    }

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

