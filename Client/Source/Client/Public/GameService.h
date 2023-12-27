// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetWork/NetService.h"

/**
 * 
 */
class CLIENT_API GameService : public ClientService
{

public:
	class NetworkSocket* GetOwner();
	void SetOwner(class NetworkSocket* owner);
	void Send(SendBufferRef sendbuffer);

	virtual void PacketHandle(PacketSessionRef& session, BYTE* buffer, int32 len) override;

private:
	class NetworkSocket* _owner;

};
