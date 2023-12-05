#include "pch.h"
#include "World.h"
#include "User.h"
#include "GameSessionManager.h"
#include "GameSession.h"
#include "Monster.h"

shared_ptr<World> GWorld = make_shared<World>();

void World::EnterUser(UserRef user)
{
	_Users[user->GetSessionKey()] = user;
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
	newMonster->SetMonsterKey(MonsterKey());
	_Monsters.insert(pair<int64, MonsterRef>(newMonster->GetMonsterKey(), newMonster));
}

void World::Update()
{
	//::todo
	//std::cout << "World Update!" << std::endl;

	for (auto& it : _Monsters)
		it.second->Update();

	GWorld->DoTimer(500, &World::Update);
}
