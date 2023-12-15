// Fill out your copyright notice in the Description page of Project Settings.


#include "AYCharacter.h"
#include "PreLoder.h"
#include "DarkNightAnimInstance.h"

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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalmesh(TEXT("/Game/Asset/GreatSword/Mannequin/Character/Mesh/WeaponMaster_GreatSword01.WeaponMaster_GreatSword01"));
	if (skeletalmesh.Succeeded())
		GetMesh()->SetSkeletalMesh(skeletalmesh.Object);

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Game/Blueprint/Character/GreatSwordAnimBP.GreatSwordAnimBP_C"));
	if (anim.Succeeded())
		GetMesh()->SetAnimInstanceClass(anim.Class);

	SetControl(eControlType::Type2);

	GetCharacterMovement()->JumpZVelocity = 450.0f;

	IsAttacking = false;
	MaxCombo = 3;
	AttackEndComboState();
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

	if (CurrentControlType == eControlType::Type2)
		TickMove();
}

void AAYCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_Anim = Cast<UDarkNightAnimInstance>(GetMesh()->GetAnimInstance());
	CHECK(_Anim);

	_Anim->OnMontageEnded.AddDynamic(this, &AAYCharacter::OnAttackMontageEnded);

	_Anim->OnNextAttackCheck.AddLambda([this]()->void {
		LOG("OnNextAttackCheck");
		CanNextCombo = false;

		if (IsComboInputOn)
		{
			AttackStartComboState();
			_Anim->JumpToAttackMontageSection(CurrentCombo);
		}});
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
	}
}

void AAYCharacter::ComboAttack()
{
	if (IsAttacking)
	{
		CHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if(CanNextCombo)
		{
			IsComboInputOn = true;
		}
	}
	else
	{
		CHECK(CurrentCombo == 0);
		AttackStartComboState();
		_Anim->PlayComboAttackMontage();
		_Anim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}

void AAYCharacter::OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted)
{
	CHECK(IsAttacking);
	CHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
}

void AAYCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	CHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1 , 1 , MaxCombo);
	LOG("CurrentCombo %d", CurrentCombo);
}

void AAYCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}


