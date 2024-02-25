// Fill out your copyright notice in the Description page of Project Settings.


#include "AYCharacter.h"
#include "PreLoder.h"
#include "DarkNightAnimInstance.h"
#include "PlayerAnimInstance.h"
#include "AYMonsterBase.h"
#include "ActorWeapon.h"
#include "../AYGameInstance.h"
#include "PlayerStatComponent.h"
#include "Components/WidgetComponent.h"
#include "CharacterWidget.h"
#include "Kismet/GameplayStatics.h"
#include "AYGameState.h"

// Sets default values
AAYCharacter::AAYCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalmesh(TEXT("/Game/Asset/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/IronMaskSK.IronMaskSK"));
	if (skeletalmesh.Succeeded())
		GetMesh()->SetSkeletalMesh(skeletalmesh.Object);

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Game/Blueprint/Character/SwordAnimBP.SwordAnimBP_C"));
	if (anim.Succeeded())
		GetMesh()->SetAnimInstanceClass(anim.Class);

	SetControl(eControlType::Type2);

	GetCharacterMovement()->JumpZVelocity = 450.0f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));

	Stat = CreateDefaultSubobject<UPlayerStatComponent>(TEXT("PLAYER_STAT"));

	IsAttacking = false;
	MaxCombo = 3;
	SyncTimer = 0.f;

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
void AAYCharacter::BeginPlay()
{
	Super::BeginPlay();

	FName weaponSocket(TEXT("RightWeaponShield"));
	Weapon = GetWorld()->SpawnActor<AActorWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	Weapon->LoadMesh(TEXT("/Game/Asset/ModularRPGHeroesPBR/Meshes/Weapons/Sword01SM.Sword01SM"));
	if (Weapon != nullptr)
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, weaponSocket);

	auto hpWidget = Cast<UCharacterWidget>(HPBar->GetUserWidgetObject());
	if (hpWidget != nullptr)
		hpWidget->BindCharacterStat(Stat);

	AAYGameState* state = Cast<AAYGameState>(UGameplayStatics::GetGameState(this));
	if (::IsValid(state))
		state->SetMyPlayer(this);
}

// Called every frame
void AAYCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector prevPos = GetActorLocation();

	prevPos.Rotation();
	if (CurrentControlType == eControlType::Type2)
		TickMove();
}

void AAYCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_Anim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	CHECK(_Anim);

	_Anim->OnAttack1_EndCheck.AddUObject(this, &AAYCharacter::AttackEndCheck);
	_Anim->OnAttackHitCheck.AddUObject(this, &AAYCharacter::AttackCheck);


}

// Called to bind functionality to input
void AAYCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//bind action
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("ComboAttack"), EInputEvent::IE_Pressed, this, &AAYCharacter::ComboAttack);

	//bind axis
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AAYCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AAYCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AAYCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AAYCharacter::Turn);
}

void AAYCharacter::TakeDamage(float dmgAmount)
{
	//
	Stat->TakeDamage(dmgAmount);
}

void AAYCharacter::UpDown(float axisValue)
{
	switch (CurrentControlType)
	{
	case AAYCharacter::eControlType::Type1:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), axisValue);
		break;
	case AAYCharacter::eControlType::Type2:
		DirectionToMove.X = axisValue;
		break;
	default:
		break;
	}
}

void AAYCharacter::LeftRight(float axisValue)
{
	switch (CurrentControlType)
	{
	case AAYCharacter::eControlType::Type1:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), axisValue);
		break;
	case AAYCharacter::eControlType::Type2:
		DirectionToMove.Y = axisValue;
		break;
	default:
		break;
	}
}

void AAYCharacter::Turn(float axisValue)
{
	switch (CurrentControlType)
	{
	case AAYCharacter::eControlType::Type1:
		AddControllerYawInput(axisValue);
		break;
	default:
		break;
	}
}

void AAYCharacter::LookUp(float axisValue)
{
	switch (CurrentControlType)
	{
	case AAYCharacter::eControlType::Type1:
		AddControllerPitchInput(axisValue);
		break;
	default:
		break;
	}
}

void AAYCharacter::SetControl(eControlType type)
{
	CurrentControlType = type;

	switch (type)
	{
	case AAYCharacter::eControlType::Type1:
		ControlType1();
		break;
	case AAYCharacter::eControlType::Type2:
		ContrilType2();
		break;
	default:
		break;
	}
}

void AAYCharacter::ControlType1()
{
	SpringArm->TargetArmLength = 450.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}

void AAYCharacter::ContrilType2()
{
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bDoCollisionTest = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}

void AAYCharacter::TickMove()
{
	if (DirectionToMove.SizeSquared() > 0.0f)
	{
		GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
		AddMovementInput(DirectionToMove);
		SetAnimState(EAnimState::Move);
	}

	if (DirectionToMove.SizeSquared() == 0.0f && _Anim->GetAnimState() == EAnimState::Move)
		SetAnimState(EAnimState::Idle);
}

void AAYCharacter::ComboAttack()
{
	SetAnimState(EAnimState::Attack1);
}

void AAYCharacter::AttackEndCheck()
{
	SetAnimState(EAnimState::Idle);
}

void AAYCharacter::AttackCheck()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.f),
		params
	);

	if (bResult)
	{
		if (IsValid(hitResult.GetActor()))
		{
			AAYMonsterBase* victim = Cast<AAYMonsterBase>(hitResult.GetActor());
			Protocol::C2P_RequestPlayerAttack sendPacket;
			sendPacket.set_victimkey(victim->GetActorKey());
			sendPacket.set_damageamount(5);

			UAYGameInstance* inst = Cast<UAYGameInstance>(GetGameInstance());
			if (IsValid(inst))
				inst->Send(sendPacket, (uint16)(EPacket_C2P_Protocol::C2P_RequestPlayerAttack));
			//REPORT SERVER
			LOG("PLAYER ATTACK CHECK");

			FVector l = victim->GetActorLocation();
			FVector l2 = GetActorLocation();

			float d = l.Distance(l, l2);
		}
	}
}

void AAYCharacter::AnimSync()
{
	FVector curPos = GetActorLocation();
	FRotator curRotator = GetActorRotation();
	FQuat curRot = GetActorQuat();
	UAYGameInstance* inst = Cast<UAYGameInstance>(GetGameInstance());

	Protocol::C2P_ReportMove packet;
	Protocol::UserData* userData = packet.mutable_userdata();
	Protocol::TransFormData* transform = userData->mutable_transform();
	transform->set_x(curPos.X);
	transform->set_y(curPos.Y);
	transform->set_z(curPos.Z);
	transform->set_yaw(curRotator.Yaw);
	userData->set_state(_Anim->GetAnimStateProtobuf());
	inst->Send(packet, (uint16)EPacket_C2P_Protocol::C2P_ReportMove);
}

void AAYCharacter::SetAnimState(EAnimState animstate)
{
	_Anim->SetAnimState(animstate);
	AnimSync();
}



