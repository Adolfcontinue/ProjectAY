// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorBox.h"

AActorBox::AActorBox()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
	Mesh->SetupAttachment(RootComponent);
	LoadMesh(TEXT("/Game/Asset/Fantastic_Village_Pack/meshes/props/container/SM_PROP_box_01.SM_PROP_box_01"));
}

void AActorBox::BeginPlay()
{
	Super::BeginPlay();
}

void AActorBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
