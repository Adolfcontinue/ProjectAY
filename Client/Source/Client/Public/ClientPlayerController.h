// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "GameFramework/PlayerController.h"
#include "ClientPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API AClientPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
};
