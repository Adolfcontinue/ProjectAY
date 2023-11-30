#pragma once
#include "JobQueue.h"

class World : public JobQueue
{
public:
	void EnterUser(UserRef user);
	void LeaveUser(UserRef user);
	void BroadCast(SendBufferRef sendBuffer);
	void BroadCastExcept(SendBufferRef sendBuffer, int64 exceptKey);

public:
	void CreateMonster();

public:
	void Update();

private:
	int64 MonsterKey() { return _MonsterKey.fetch_add(1); }

private:
	Atomic<int64> _MonsterKey = 0;

private:
	map<int64, UserRef> _Users;
	map<int64, MonsterRef> _Monsters;
};

extern shared_ptr<World> GWorld;