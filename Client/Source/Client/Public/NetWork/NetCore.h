// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
#include "NetHeader.h"

class CLIENT_API NetObject : public enable_shared_from_this<NetObject>
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(class NetEvent* iocpEvent, int32 numOfBytes = 0) abstract;
};

class CLIENT_API NetCore
{
public:
	NetCore();
	~NetCore();

	HANDLE		GetHandle() { return _iocpHandle; }

	bool		Register(NetObjectRef iocpObject);
	bool		Dispatch(uint32 timeoutMs = INFINITE);

private:
	HANDLE		_iocpHandle;
};
