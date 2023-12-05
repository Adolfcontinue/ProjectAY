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
	class ANetSocket* GetOwner();
	void SetOwner(ANetSocket* owner);
	void ServicePacketHandler(PacketSessionRef& session, BYTE* buffer, int32 len);
	void Send(SendBufferRef sendbuffer);


private:
	class ANetSocket* _owner;

};
