#pragma once

class GameSession;

using GameSessionRef = shared_ptr<GameSession>;

class GameSessionManager
{
public:
	void Add(GameSessionRef session);
	void Add(int64 sessionKey, GameSessionRef session);
	void Remove(GameSessionRef session);
	void Remove(int64 sessionKey);
	void BroadCast(SendBufferRef sendBuffer);
	GameSessionRef Find(int64 sessionKey);

public:
	GameSessionRef CreateSession();

public:
	inline int64 FindSessionKey() { return _sessionKey.fetch_add(1); }

private:
	USE_LOCK;
	set<GameSessionRef> _sessions;
	map<int64, GameSessionRef> _sessionMap;
	Atomic<int64> _sessionKey = 0;
};

extern GameSessionManager GGameSessionManager;

