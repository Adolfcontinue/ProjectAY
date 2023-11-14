#include "pch.h"
#include "ClientPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

// Á÷Á¢ ÄÁÅÙÃ÷ ÀÛ¾÷ÀÚ

bool Handler::Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	return false;
}

bool Handler::C2P_RequestLogin(PacketSessionRef& session, Protocol::C2P_RequestLogin& packet)
{
	if (packet.id().empty())
		return false;

	if (packet.id().empty())
		return false;

	//::todo db

	Protocol::P2C_ResultLogin send;
	send.set_result((uint32)true);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(send);
	session->Send(sendBuffer);
	return true;
}

