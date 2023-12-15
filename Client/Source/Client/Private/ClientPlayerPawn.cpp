// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientPlayerPawn.h"

// Sets default values
AClientPlayerPawn::AClientPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletamesh(TEXT("/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/DarkKnightSK.DarkKnightSK"));
	if (skeletamesh.Succeeded())
	{
		Mesh->SetSkeletalMesh(skeletamesh.Object);
	}

	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Game/ThirdPerson/Maps/darknightAnimBluePrint.darknightAnimBluePrint_C"));
	if (anim.Succeeded())
	{
		Mesh->SetAnimInstanceClass(anim.Class);
	}

}

// Called when the game starts or when spawned
void AClientPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClientPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClientPlayerPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	LOG_S(Warning);
}

void AClientPlayerPawn::PossessedBy(AController* newController)
{
	LOG_S(Warning);
	Super::PossessedBy(newController);
}

// Called to bind functionality to input
void AClientPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AClientPlayerPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AClientPlayerPawn::LeftRight);
}

void AClientPlayerPawn::UpDown(float axisValue)
{
	AddMovementInput(GetActorForwardVector(), axisValue);
}

void AClientPlayerPawn::LeftRight(float axisValue)
{
	AddMovementInput(GetActorRightVector(), axisValue);
}

