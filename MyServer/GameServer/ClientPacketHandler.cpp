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
	user->SetExp(0);
	user->SetID(packet.id());
	user->SetPW(packet.pw());
	user->SetLevel(1);
	user->SetSessionKey(session->GetSessionKey());
	user->GetTransForm()->SetPosition(790.f, 1110.f, 90.f);
	user->GetTransForm()->SetRotation(0.f, 0.f, 0.f, 1.f);
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
	DirectX::XMFLOAT3 pos;
	ProtobufHelper::ConvertXMFLOAT3(&pos, packet.posdata().posision());
	DirectX::XMFLOAT4 rot;
	ProtobufHelper::ConvertXMFLOAT4(&rot, packet.posdata().rotation());
	GWorld->DoASync(&World::MoveUser, session->GetSessionKey(), pos, rot);

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


