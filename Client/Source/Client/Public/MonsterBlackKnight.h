// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AYMonsterBase.h"
#include "MonsterBlackKnight.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API AMonsterBlackKnight : public AAYMonsterBase
{
	GENERATED_BODY()
	

public:
	AMonsterBlackKnight();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
};
