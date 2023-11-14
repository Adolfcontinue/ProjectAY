// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SocketInstance.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API USocketInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	virtual void Test();
	
	//clientsocket 
};
