// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AYMonsterBase.h"
#include "MonsterBeholder.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API AMonsterBeholder : public AAYMonsterBase
{
	GENERATED_BODY()
	
public:
	AMonsterBeholder();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
