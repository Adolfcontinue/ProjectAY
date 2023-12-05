// Fill out your copyright notice in the Description page of Project Settings.


#include "GameService.h"
#include "NetSocket.h"


ANetSocket* GameService::GetOwner()
{
	return _owner;
}

void GameService::SetOwner(ANetSocket* owner)
{
	_owner = owner;
}

void GameService::ServicePacketHandler(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	_owner->NetSocketPacketHandler(session, buffer, len);
}

void GameService::Send(SendBufferRef sendbuffer)
{
	GetSession()->Send(sendbuffer);
}
