#include "pch.h"
#include "GameSessionManager.h"
#include "GameSession.h"

GameSessionManager GGameSessionManager;

void GameSessionManager::Add(GameSessionRef session)
{
	WRITE_LOCK;
	_sessions.insert(session);
}

void GameSessionManager::Add(int64 sessionKey, GameSessionRef session)
{
	WRITE_LOCK;
	_sessionMap.insert(make_pair(sessionKey, session));
}

void GameSessionManager::Remove(GameSessionRef session)
{
	WRITE_LOCK;
	_sessions.erase(session);
}

void GameSessionManager::Remove(int64 sessionKey)
{
	WRITE_LOCK;
	_sessionMap.erase(sessionKey);
}

void GameSessionManager::BroadCast(SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	for (GameSessionRef session : _sessions)
	{
		session->Send(sendBuffer);
	}
}

void GameSessionManager::BroadCast(SendBufferRef sendBuffer, int64 except)
{
	WRITE_LOCK;
	for (GameSessionRef session : _sessions)
	{
		if (session->GetSessionKey() == except)
			continue;

		session->Send(sendBuffer);
	}
}


GameSessionRef GameSessionManager::Find(int64 sessionKey)
{
	auto iter = _sessionMap.find(sessionKey);
	if (iter == _sessionMap.end())
		return nullptr;

	return iter->second;
}

GameSessionRef GameSessionManager::CreateSession()
{
	GameSessionRef retval = MakeShared<GameSession>();
	retval->SetSessionKey(IssueSessionKey());
	return retval;
}
