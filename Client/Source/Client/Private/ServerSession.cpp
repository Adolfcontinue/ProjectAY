// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerSession.h"
#include "GameService.h"


ServerSession::ServerSession()
{
}

ServerSession::~ServerSession()
{
}

void ServerSession::OnConnected()
{
}

void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef session = GetPacketSessionRef();
	GetService()->PacketHandle(session, buffer, len);
}

void ServerSession::OnSend(int32 len)
{
}

void ServerSession::OnDisconnected()
{
}
