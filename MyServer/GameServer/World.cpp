#include "pch.h"
#include "World.h"
#include "User.h"
#include "GameSessionManager.h"
#include "GameSession.h"
#include "Monster.h"
#include "ProtobufHelper.h"
#include "ClientPacketHandler.h"
#include "ConsoleLogger.h"

shared_ptr<World> GWorld = make_shared<World>();

void World::EnterUser(UserRef user)
{
	user->SetActorKey(IssueActorKey());
	_Users[user->GetSessionKey()] = user;

	Protocol::P2C_ReportEnterUser packet;
	Protocol::UserData* data = packet.mutable_user();
	Protocol::Vector* loc = data->mutable_pos();
	ProtobufHelper::ConvertVector(loc, user->GetPosX(), user->GetPosY(), user->GetPosZ());

	Protocol::Vector* rot = data->mutable_rot();
	ProtobufHelper::ConvertVector(rot, user->GetRotX(), user->GetRotY(), user->GetRotZ());
	
	data->set_userkey(user->GetSessionKey());
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
	BroadCastExcept(sendBuffer, user->GetSessionKey());
}

void World::LeaveUser(int64 sessionKey)
{
	auto iter = _Users.find(sessionKey);
	if (iter == _Users.end())
		return;

	_Users.erase(sessionKey);

	Protocol::P2C_ReportLeaveUser packet;
	packet.set_userkey(sessionKey);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(packet);
	BroadCastExcept(sendBuffer, sessionKey);
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

UserRef World::FindUser(int64 key)
{
	auto iter = _Users.find(key);
	if (iter == _Users.end())
		return nullptr;

	return iter->second;
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
	for (auto& it : _Monsters)
		it.second->Update();

	GWorld->DoTimer(500, &World::Update);
}
