// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
#include "NetWork/NetSession.h"
#include "Protocol.pb.h"
#include "NetPacketHandler.h"


class CLIENT_API ServerSession : public PacketSession
{
public:
	ServerSession();
	~ServerSession();

public:
	virtual void OnConnected() override
	{
		int a = 0;
		Protocol::C2P_RequestLogin p;
		p.set_id("aaa");
		p.set_pw("123");

		auto sss = NetPacketHandler::MakeSendBuffer(p);
		Send(sss);
	}

	virtual void OnRecvPacket(BYTE* buffer, int32 len) override
	{
		PacketSessionRef session = GetPacketSessionRef();
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		NetPacketHandler::HandlePacket(session, buffer, len);
	}

	virtual void OnSend(int32 len) override
	{

	}

	virtual void OnDisconnected() override
	{

	}

};
