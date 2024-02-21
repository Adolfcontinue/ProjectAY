#include "pch.h"
#include "ClientPacketHandler.h"
#include "QueryRunManager.h"
#include "MSDBQuery.h"
#include "GameSessionManager.h"
#include "GameSession.h"
#include "Collision.h"
#include "World.h"
#include "User.h"
#include "Monster.h"
#include "ProtobufHelper.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];


bool Handler::Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	return false;
}

bool Handler::C2P_RequestLogin(PacketSessionRef& session, Protocol::C2P_RequestLogin& packet)
{
	//::todo login data db
	UserRef user = MakeShared<User>();
	user->Init(session->GetSessionKey(), packet.id(), packet.pw(), 
		790.f, 1100.f, 90.f, 1,  0.f, 0, 10.f, 100.f);
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
	GWorld->DoASync(&World::MoveUser, session->GetSessionKey(), packet.userdata().transform(), packet.userdata().state());
	return true;
}

bool Handler::C2P_RequestPlayerAttack(PacketSessionRef& session, Protocol::C2P_RequestPlayerAttack& packet)
{
	//vaild
	uint64 victimkey = packet.victimkey();
	MonsterRef monster = GWorld->FindMonster(victimkey);
	if (monster == nullptr)
		return false;

	monster->DoASync(&Monster::TakeDamage, (uint64)session->GetSessionKey(), packet.damageamount());

	return true;
}


