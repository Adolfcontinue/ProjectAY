// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GamePlayer.h"
#include "ClientGameMode.generated.h"

UCLASS(minimalapi)
class AClientGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AClientGameMode();

public:
	void CreatePlayer(uint64 playerKey);
	void AddPlayer(AGamePlayer* player);
	void ErasePlaye(uint64 playerKey);
	AGamePlayer* FindPlayer(uint64 playerKey);

private:
	TMap<uint64, AGamePlayer*> _players;
};



