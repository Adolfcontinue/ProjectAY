// Fill out your copyright notice in the Description page of Project Settings.


#include "GameService.h"
#include "NetSocket.h"
#include "NetworkSocket.h"



NetworkSocket* GameService::GetOwner()
{
	return _owner;
}

void GameService::SetOwner(NetworkSocket* owner)
{
	_owner = owner;
}

//void GameService::ServicePacketHandler(PacketSessionRef& session, BYTE* buffer, int32 len)
//{
//	_owner->NetSocketPacketHandler(session, buffer, len);
//}

void GameService::Send(SendBufferRef sendbuffer)
{
	GetSession()->Send(sendbuffer);
}

void GameService::PacketHandle(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	_owner->NetSocketPacketHandler(session, buffer, len);
}
