// Fill out your copyright notice in the Description page of Project Settings.


#include "NetPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handler::Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	return false;
}

bool Handler::P2C_ResultLogin(PacketSessionRef& session, Protocol::P2C_ResultLogin& packet)
{
	int aaa = packet.result();

	return false;
}

bool Handler::P2C_ReportMove(PacketSessionRef& session, Protocol::P2C_ReportMove& packet)
{
	return false;
}

bool Handler::P2C_ResultCollision(PacketSessionRef& session, Protocol::P2C_ResultCollision& packet)
{
	return false;
}

bool Handler::P2C_ReportUpdateMonsters(PacketSessionRef& session, Protocol::P2C_ReportUpdateMonsters& packet)
{
	return false;
}
