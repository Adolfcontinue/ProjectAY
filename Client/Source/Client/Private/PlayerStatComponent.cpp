// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatComponent.h"

// Sets default values for this component's properties
UPlayerStatComponent::UPlayerStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	Level = 1;
	// ...
}


// Called when the game starts
void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UPlayerStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}


// Called every frame
void UPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerStatComponent::SetNewLevel(int32 level)
{
	//todo
	Level = level;
	CurrentHP = 100;
}

void UPlayerStatComponent::TakeDamage(float dmg)
{
	CurrentHP = FMath::Clamp(CurrentHP - dmg, 0.f, 100);
	SetHP(CurrentHP);
}

void UPlayerStatComponent::SetHP(float hp)
{
	CurrentHP = hp;
	OnHPchanged.Broadcast();
}

float UPlayerStatComponent::GetAttack()
{
	//todo
	return 5.0f;
}

float UPlayerStatComponent::GetHPRatio()
{
	return (CurrentHP / 100);
}

