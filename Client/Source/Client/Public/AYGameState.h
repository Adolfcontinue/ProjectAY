// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "OtherCharacter.h"
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

private:
	TMap<int64, AOtherCharacter*> Players;


};
