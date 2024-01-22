// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AYActorBase.h"
#include "ActorBox.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API AActorBox : public AAYActorBase
{
	GENERATED_BODY()
	
public:
	AActorBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* Trigger;
};
