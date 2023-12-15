// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "GameFramework/GameModeBase.h"
#include "AYGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API AAYGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AAYGameMode();

	virtual void PostLogin(APlayerController* newPlayer) override;
};
