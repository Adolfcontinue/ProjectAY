#include "pch.h"
#include "World.h"
#include "User.h"
#include "GameSessionManager.h"
#include "GameSession.h"
#include "Monster.h"
#include "Protocol.pb.h"
#include "Struct.pb.h"
#include "ClientPacketHandler.h"
#include "ConsoleLogger.h"

shared_ptr<World> GWorld = make_shared<World>();

void World::EnterUser(UserRef user)
{
	user->SetActorKey(IssueActorKey());
	_Users[user->GetSessionKey()] = user;

	//Protocol::UserData enterUser;
	//enterUser.set_userkey(user->GetSessionKey());
	//Protocol::Vector* v = enterUser.mutable_pos();
	//v->set_x(0);
	//v->set_y(0);
	//v->set_z(0);
	//enterUser.set_userkey(user->GetActorKey());
	//enterUser.set_col_r(1.0);

	//Protocol::P2C_ReportEnterUser packet;
	//Protocol::UserData* data = packet.mutable_user();
	//data->set_userkey(user->GetSessionKey());
	//Protocol::Vector* v = data->mutable_pos();
	//v->set_x(0);
	//v->set_y(0);
	//v->set_z(0);
	//data->set_userkey(user->GetActorKey());
	//data->set_col_r(1.0);
	//SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
	//DoASync(&World::BroadCast,sendBuffer);
	//BroadCast(sendBuffer);
	//BroadCastExcept(sendBuffer, user->GetSessionKey());
}

void World::LeaveUser(int64 sessionKey)
{
	auto iter = _Users.find(sessionKey);
	if (iter == _Users.end())
		return;

	/*Protocol::P2C_ReportLeaveUser packet;
	Protocol::UserData* data = packet.mutable_user();
	data->set_userkey(iter->second->GetActorKey());
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
	DoASync(&World::BroadCast, sendBuffer);
	_Users.erase(sessionKey);*/
}

void World::BroadCast(SendBufferRef sendBuffer)
{
	for (auto& user : _Users)
	{
		GameSessionRef sessison = GGameSessionManager.Find(user.first);
		if (sessison != nullptr)
			sessison->Send(sendBuffer);
	}
}

void World::BroadCastExcept(SendBufferRef sendBuffer, int64 exceptKey)
{
	for (auto& user : _Users)
	{
		if (user.first == exceptKey)
			continue;

		GameSessionRef sessison = GGameSessionManager.Find(user.first);
		if (sessison != nullptr)
			sessison->Send(sendBuffer);
	}
}

//::todo create monster
void World::CreateMonster()
{
	MonsterRef newMonster = MakeShared<Monster>();
	newMonster->SetActorKey(IssueActorKey());
	_Monsters.insert(pair<int64, MonsterRef>(newMonster->GetActorKey(), newMonster));
}

void World::Update()
{
	//::todo
	//std::cout << "World Update!" << std::endl;

	for (auto& it : _Monsters)
		it.second->Update();

	GWorld->DoTimer(500, &World::Update);
}
