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
	Float3 pos;
	pos._x = 790;
	pos._y = 1110;
	pos._z = 90;
	user->SetPos(pos);
	Float3 rot;
	rot._x = 0;
	rot._y = 0;
	rot._z = 0;
	user->SetRot(rot);
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

bool Handler::C2P_ReportMove(PacketSessionRef& session, Protocol::C2P_ReportMove& packet)
{
	Float3 pos;
	pos._x = packet._pos().x();
	pos._y = packet._pos().y();
	pos._z = packet._pos().z();

	GWorld->DoASync(&World::MoveUser, session->GetSessionKey(), pos);
	return true;
}


