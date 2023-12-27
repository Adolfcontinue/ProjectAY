// Fill out your copyright notice in the Description page of Project Settings.


#include "AYTickObject.h"

void UAYTickObject::CallTimer()
{
	FTimerHandle tHandle;
	const float Delay = 1.0f;
	GetWorld()->GetTimerManager().SetTimer(tHandle, this, &UAYTickObject::TestTimer, Delay, false);
}

void UAYTickObject::TestTimer()
{
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, "Hello World");
}

void UAYTickObject::Tick(float DeltaTime)
{
	TestCounter += DeltaTime;
}

bool UAYTickObject::IsTickable() const
{
	return true;
}

bool UAYTickObject::IsTickableInEditor() const
{
	return true;
}

bool UAYTickObject::IsTickableWhenPaused() const
{
	return false;
}

TStatId UAYTickObject::GetStatId() const
{
	return TStatId();
}

UWorld* UAYTickObject::GetWorld() const
{
	return GetOuter()->GetWorld();
}
