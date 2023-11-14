#include "pch.h"
#include "World.h"
#include "User.h"
#include "GameSessionManager.h"
#include "GameSession.h"

void World::Enter(UserRef user)
{
	WRITE_LOCK;
	_users[user->GetSessionKey()] = user;
}

void World::Leave(UserRef user)
{
	WRITE_LOCK;
	_users.erase(user->GetSessionKey());
}

void World::BroadCast(SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	for (auto& p : _users)
	{
		GameSessionRef sessison = GGameSessionManager.Find(p.first);
		if (sessison != nullptr)
			sessison->Send(sendBuffer);
	}
}
