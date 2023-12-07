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

	Protocol::UserData enterUser;
	Protocol::Vector pos = user->GetPos()->Convert();
	enterUser.set_userkey(user->GetSessionKey());
	enterUser.set_allocated_pos(&pos);
	enterUser.set_userkey(user->GetActorKey());
	enterUser.set_col_r(1.0);

	Protocol::P2C_ReportEnterUser packet;
	packet.set_allocated_user(&enterUser);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
	BroadCastExcept(sendBuffer, user->GetSessionKey());
}

void World::LeaveUser(UserRef user)
{
	_Users.erase(user->GetSessionKey());
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
