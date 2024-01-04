#include "pch.h"
#include "ClientPacketHandler.h"
#include "QueryRunManager.h"
#include "MSDBQuery.h"
#include "GameSessionManager.h"
#include "GameSession.h"
#include "Collision.h"
#include "World.h"
#include "User.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

// Á÷Á¢ ÄÁÅÙÃ÷ ÀÛ¾÷ÀÚ

bool Handler::Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	return false;
}

bool Handler::C2P_RequestLogin(PacketSessionRef& session, Protocol::C2P_RequestLogin& packet)
{
	//::todo login data db
	UserRef user = MakeShared<User>();
	user->SetExp(0);
	user->SetID(packet.id());
	user->SetPW(packet.pw());
	user->SetLevel(1);
	user->SetSessionKey(session->GetSessionKey());
	user->SetPos(make_shared<Float3>(790, 1110, 90));
	user->SetRot(make_shared<Float3>(0, 0, 0));
	GWorld->DoASync(&World::EnterUser, user);
	Protocol::P2C_ResultLogin sendPacket;
	sendPacket.set_result((uint32)true);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);

	return true;
}

bool Handler::C2P_RequestWorldData(PacketSessionRef& session, Protocol::C2P_RequestWorldData& packet)
{
	UserRef user = GWorld->FindUser(session->GetSessionKey());
	if (user == nullptr)
		return false;

	user->DoASync(&User::ReqWorldData);
	return true;
}


