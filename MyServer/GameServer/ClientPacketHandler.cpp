#include "pch.h"
#include "ClientPacketHandler.h"
#include "QueryRunManager.h"
#include "MSDBQuery.h"
#include "GameSessionManager.h"
#include "GameSession.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

// ���� ������ �۾���

bool Handler::Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	return false;
}

bool Handler::C2P_RequestLogin(PacketSessionRef& session, Protocol::C2P_RequestLogin& packet)
{
	//::todo db
	
	Protocol::P2C_ResultLogin sendPacket;
	sendPacket.set_result((uint32)true);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);

	return true;
}

bool Handler::C2P_ReportMove(PacketSessionRef& session, Protocol::C2P_ReportMove& packet)
{
	if (session == nullptr)
		return false;

	Protocol::P2C_ReportMove sendPacket;
	sendPacket.set_sessionkey(session->GetSessionKey());
	sendPacket.set_posx(packet.posx());
	sendPacket.set_posy(packet.posy());
	sendPacket.set_posz(packet.posz());

	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	
	GGameSessionManager.BroadCast(sendBuffer, session->GetSessionKey());

	return false;
}

