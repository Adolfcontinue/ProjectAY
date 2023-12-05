// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
#include "Engine/World.h"
#include "NetWork/NetSession.h"
#include "Protocol.pb.h"
#include "NetPacketHandler.h"


class CLIENT_API ServerSession : public PacketSession
{
public:
	ServerSession();
	~ServerSession();

public:
	//connncet process
	virtual void OnConnected() override;
	//packet recv process
	virtual void OnRecvPacket(BYTE* buffer, int32 len) override; 
	//packet send process
	virtual void OnSend(int32 len) override;
	//disconnect procees
	virtual void OnDisconnected() override;
	

};
