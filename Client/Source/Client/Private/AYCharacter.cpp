// Fill out your copyright notice in the Description page of Project Settings.


#include "AYCharacter.h"
#include "PreLoder.h"
#include "DarkNightAnimInstance.h"
#include "PlayerAnimInstance.h"
#include "../AYGameInstance.h"

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
	SpringArm->TargetArmLength = 400.0f;
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

	IsAttacking = false;
	MaxCombo = 3;
	SyncTimer = 0.f;

	/// Script / Engine.StaticMesh'/Game/Asset/ModularRPGHeroesPBR/Meshes/Weapons/Sword07SM.Sword07SM'
	FName weaponSocket(TEXT("RightWeaponShield"));
	if (GetMesh()->DoesSocketExist(weaponSocket))
	{
		Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> weaponMesh(TEXT("/Game/Asset/ModularRPGHeroesPBR/Meshes/Weapons/Sword07SM.Sword07SM"));
		if (weaponMesh.Succeeded())
			Weapon->SetStaticMesh(weaponMesh.Object);

		Weapon->SetupAttachment(GetMesh(), weaponSocket);
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));
}

// Called when the game starts or when spawned
void AAYCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAYCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector prevPos = GetActorLocation();

	if (CurrentControlType == eControlType::Type2)
		TickMove();
}

void AAYCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_Anim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	CHECK(_Anim);

	_Anim->OnAttack1_EndCheck.AddUObject(this, &AAYCharacter::AttackEndCheck);
	_Anim->OnAttack2_EndCheck.AddUObject(this, &AAYCharacter::AttackEndCheck2);
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
	SpringArm->TargetArmLength = 800.f;
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
	if (_Anim->GetAnimState() == EAnimState::Attack1)
		IsAttacking = true;
	else
		SetAnimState(EAnimState::Attack1);
}

void AAYCharacter::AttackEndCheck()
{
	if (IsAttacking)
		SetAnimState(EAnimState::Attack2);
	else
		SetAnimState(EAnimState::Idle);
}

void AAYCharacter::AttackEndCheck2()
{
	SetAnimState(EAnimState::Idle);
	IsAttacking = false;
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
			//REPORT SERVER
			LOG("PLAYER ATTACK CHECK");
		}
	}
}

void AAYCharacter::AnimSync()
{
	FVector curPos = GetActorLocation();
	FQuat curRot = GetActorQuat();
	UAYGameInstance* inst = Cast<UAYGameInstance>(GetGameInstance());

	Protocol::C2P_ReportMove packet;
	Protocol::PositionData* posData = packet.mutable_posdata();
	Protocol::Float3* pos = posData->mutable_posision();
	pos->set_x(curPos.X);
	pos->set_y(curPos.Y);
	pos->set_z(curPos.Z);
	Protocol::Float4* rot = posData->mutable_rotation();
	rot->set_x(curRot.X);
	rot->set_y(curRot.Y);
	rot->set_z(curRot.Z);
	rot->set_w(curRot.W);

	packet.set_state(_Anim->GetAnimStateProtobuf());
	inst->Send(packet, (uint16)EPacket_C2P_Protocol::C2P_ReportMove);
}

void AAYCharacter::SetAnimState(EAnimState animstate)
{
	_Anim->SetAnimState(animstate);
	AnimSync();
}


