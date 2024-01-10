// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherCharacter.h"

// Sets default values
AOtherCharacter::AOtherCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalmesh(TEXT("/Game/Asset/GreatSword/Mannequin/Character/Mesh/WeaponMaster_GreatSword01.WeaponMaster_GreatSword01"));
	if (skeletalmesh.Succeeded())
		GetMesh()->SetSkeletalMesh(skeletalmesh.Object);

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Game/Blueprint/Character/GreatSwordAnimBP.GreatSwordAnimBP_C"));
	if (anim.Succeeded())
		GetMesh()->SetAnimInstanceClass(anim.Class);

	GetCharacterMovement()->JumpZVelocity = 450.0f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));
}

// Called when the game starts or when spawned
void AOtherCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOtherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetLocation.Size() > 0)
		Move(DeltaTime);

	if (TargetRotation.Size() > 0)
		Rotation(DeltaTime);
}

// Called to bind functionality to input
void AOtherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AOtherCharacter::Move(float DeltaTime)
{
	// ���� ����ġ�� �������� �ε巯�� �̵��� ����
	LerpAlpha += DeltaTime * 2.0f; // 2.0f�� ���� �ӵ� ���� ��

	// ���� ����ġ�� [0, 1] ������ Ŭ����
	LerpAlpha = FMath::Clamp(LerpAlpha, 0.0f, 1.0f);

	// ���� ������ ����� ���� ��ġ�� ��ǥ ��ġ�� �ε巴�� �̵���Ŵ
	FVector NewLocation = FMath::Lerp(CurrentLocation, TargetLocation, LerpAlpha);
	SetActorLocation(NewLocation);
}

void AOtherCharacter::Rotation(float DeltaTime)
{
	SlerpAlpha += DeltaTime * 2.0f; // ���� �ӵ� ���� �� (2.0f�� ����, ���� �ʿ�)
	SlerpAlpha = FMath::Clamp(SlerpAlpha, 0.0f, 1.0f); // [0, 1] ������ Ŭ����

	// ���ʹϾ� Slerp�� ����� ���� ȸ���� ��ǥ ȸ������ �ε巴�� �̵���Ŵ
	FQuat NewRotation = FQuat::Slerp(CurrentRotation, TargetRotation, SlerpAlpha);
	SetActorRotation(NewRotation);
}

