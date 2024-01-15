// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "OtherCharacter.h"
#include "AYMonsterBase.h"
#include "AYGameState.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API AAYGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	void AddPlayer(int64 key, AOtherCharacter* player);
	void RemovePlayer(int64 key);
	AOtherCharacter* FindPlayer(int64 key);

	void AddMonster(int64 key, AAYMonsterBase* monster);
	AAYMonsterBase* FindMonster(int64 key);

public:
	void RepPlayerMove(int64 userKey, FVector pos, FQuat quat);


private:
	TMap<int64, AOtherCharacter*> Players;
	TMap<int64, AAYMonsterBase*> Monsters;
};
