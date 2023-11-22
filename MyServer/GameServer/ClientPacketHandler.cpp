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
	//::todo login data
	UserRef user = MakeShared<User>();
	user->SetExp(0);
	user->SetID(packet.id());
	user->SetPW(packet.pw());
	user->SetLevel(1);
	user->SetSessionKey(session->GetSessionKey());

	GWorld->DoASync(&World::EnterUser, user);
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

	//valid
	//todo vaild
	
	//process
	Protocol::P2C_ReportMove sendPacket;
	Protocol::UserData* user = nullptr;
	user->set_userkey(packet.user().userkey());
	Protocol::Vector vec = packet.user().pos();
	user->set_allocated_pos(&vec);

	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	
	GWorld->DoASync(&World::BroadCast, sendBuffer);

	//GGameSessionManager.BroadCast(sendBuffer, session->GetSessionKey());
	return false;
}

bool Handler::C2P_RequestCollison(PacketSessionRef& session, Protocol::C2P_RequestCollison& packet)
{
	SVector srcVec = SVector(packet.src().pos().x(), packet.src().pos().y(), packet.src().pos().z());
	double srcR = packet.src().col_r();
	const int32 size = packet.descdatas_size();

	//valid
	//todo valid


	//process
	vector<Protocol::MonsterData> vec;
	for (int i = 0; i < size; ++i)
	{
		Protocol::MonsterData monster = packet.descdatas(i);
		SVector descVec = SVector(monster.pos().x(), monster.pos().y(), monster.pos().z());
		double descR = monster.cor_r();

		if (Collision::SphereToSphere(srcVec, srcR, descVec, descR))
		{
			//todo
			vec.push_back(monster);
		}
	}
	

	Protocol::P2C_ResultCollision sendPacket;
	for (int i = 0; i < vec.size(); ++i)
	{
		Protocol::MonsterData* mon = sendPacket.add_descdatass();
		mon->set_cor_r(vec[i].cor_r());
		mon->set_hp(vec[i].hp());
		mon->set_monsterkey(vec[i].monsterkey());
		Protocol::Vector pos = vec[i].pos();
		mon->set_allocated_pos(&pos);
	}

	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);

	Protocol::P2C_ReportUpdateMonsters reportPacket;
	for (int i = 0; i < vec.size(); ++i)
	{
		Protocol::MonsterData* mon = sendPacket.add_descdatass();
		mon->set_cor_r(vec[i].cor_r());
		mon->set_hp(vec[i].hp());
		mon->set_monsterkey(vec[i].monsterkey());
		Protocol::Vector pos = vec[i].pos();
		mon->set_allocated_pos(&pos);
	}

	SendBufferRef reportBuffer = ClientPacketHandler::MakeSendBuffer(reportPacket);
	//GGameSessionManager.BroadCast(reportBuffer, session->GetSessionKey());

	GWorld->DoASync(&World::BroadCast, reportBuffer);
	return true;
}

