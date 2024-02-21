#include "pch.h"
#include "World.h"
#include "User.h"
#include "GameSessionManager.h"
#include "GameSession.h"
#include "Monster.h"
#include "ProtobufHelper.h"
#include "ClientPacketHandler.h"
#include "ConsoleLogger.h"
#include "Actor.h"
#include "Random.h"

shared_ptr<World> GWorld = make_shared<World>();

void World::Init()
{
	Map = new GridMap();
	Map->CreateDefaultGridNode();
	CreateMonster();
}

void World::EnterUser(UserRef user)
{
	user->SetActorKey(IssueActorKey());
	_Users[user->GetSessionKey()] = user;

	Protocol::P2C_ReportEnterUser packet;
	Protocol::UserData* data = packet.mutable_user();
	Protocol::TransFormData* transform = data->mutable_transform();
	Protocol::TransFormData* userTransForm = user->GetTransFormAgent()->GetTransForm();
	transform->CopyFrom(*userTransForm);
	data->set_userkey(user->GetSessionKey());
	data->set_sessionkey(user->GetSessionKey());
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


void World::MoveUser(int64 sessionKey, Protocol::TransFormData transform, Protocol::ActorState state)
{
	UserRef user = FindUser(sessionKey);
	if (user == nullptr)
		return;

	user->GetTransFormAgent()->SetTransForm(&transform);

	Protocol::P2C_ReportMove sendPacket;
	Protocol::UserData* userData = sendPacket.mutable_userdata();
	userData->set_userkey(sessionKey);
	userData->set_userkey(sessionKey);
	Protocol::TransFormData* transFormData = userData->mutable_transform();
	transFormData->CopyFrom(transform);
	userData->set_state(state);
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	BroadCastExcept(sendBuffer, sessionKey);
}

MonsterRef World::FindMonster(uint64 key)
{
	auto iter = _Monsters.find(key);
	if (iter == _Monsters.end())
		return nullptr;

	return iter->second;
}

GridMap* World::GetGridMap()
{
	return Map;
}

//::todo create monster
void World::CreateMonster()
{
	/*for (int i = 0; i < 1; ++i)
	{
		float x = Random::GetRandom(50, 5500);
		float y = Random::GetRandom(50, 5500);
		float z = 90.f;
		MonsterRef newMonster = MakeShared<Monster>();
		newMonster->Init(IssueActorKey(), eMonsterType::Beholder, x, y, z, 0);
		_Monsters.insert(pair<int64, MonsterRef>(newMonster->GetActorKey(), newMonster));
	}*/

	float x = Random::GetRandom(50, 5500);
	float y = Random::GetRandom(50, 5500);
	float z = 70.f;
	
	x = 800;
	y = 1500;

	MonsterRef newMonster = MakeShared<Monster>();
	newMonster->Init(IssueActorKey(), eMonsterType::Beholder, x, y, z, -90.f);
	_Monsters.insert(pair<int64, MonsterRef>(newMonster->GetActorKey(), newMonster));
}


void World::Update()
{
	for (auto& it : _Monsters)
		it.second->Update();

	DoTimer(2000, &World::Update);
}

