// Fill out your copyright notice in the Description page of Project Settings.


#include "AYActorBase.h"

// Sets default values
AAYActorBase::AAYActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void AAYActorBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAYActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAYActorBase::LoadMesh(FString& path)
{
	UStaticMesh* staticMesh = LoadObject<UStaticMesh>(nullptr, *path);
	if (IsValid(staticMesh))
		Mesh->SetStaticMesh(staticMesh);
}

void AAYActorBase::SetScale(FVector& scale)
{
	Mesh->SetRelativeScale3D(scale);
}

UStaticMeshComponent* AAYActorBase::GetStaticMeshComponent()
{
	return Mesh;
}

