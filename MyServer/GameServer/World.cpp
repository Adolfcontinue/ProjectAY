#include "pch.h"
#include "World.h"
#include "User.h"
#include "GameSessionManager.h"
#include "GameSession.h"

shared_ptr<World> GWorld = make_shared<World>();

void World::EnterUser(UserRef user)
{
	_users[user->GetSessionKey()] = user;
}

void World::LeaveUser(UserRef user)
{
	_users.erase(user->GetSessionKey());
}

void World::BroadCast(SendBufferRef sendBuffer)
{
	for (auto& p : _users)
	{
		GameSessionRef sessison = GGameSessionManager.Find(p.first);
		if (sessison != nullptr)
			sessison->Send(sendBuffer);
	}
}
