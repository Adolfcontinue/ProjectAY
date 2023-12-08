// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Public/NetSocket.h"
#include "AYGameInstance.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_TwoParams(handlerz, int, int);

UCLASS()
class CLIENT_API UAYGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	virtual void Init();

public:
	ANetSocket* GetSocket();

private:
	ANetSocket* _socket;

public:
	template<typename T>
	void Send(T& packet, uint16 col);
};

template<typename T>
inline void UAYGameInstance::Send(T& packet, uint16 col)
{
	_socket->Send<T>(packet, col);
}
