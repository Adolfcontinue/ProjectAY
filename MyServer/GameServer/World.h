#pragma once
#include "Float3.h"
#include "JobQueue.h"

class World : public JobQueue
{
	friend class User;

public:
	void EnterUser(UserRef user);
	void LeaveUser(int64 sessionKey);
	void BroadCast(SendBufferRef sendBuffer);
	void BroadCastExcept(SendBufferRef sendBuffer, int64 exceptKey);
	UserRef FindUser(int64 key);
	void MoveUser(int64 sessionKey, Float3 pos, Float4 rot, Protocol::PlayerState state);

	MonsterRef FindMonster(uint64 key);
	


public:
	void CreateMonster();

public:
	void Update();

private:
	int64 IssueActorKey() { return _ActorKey.fetch_add(1); }

private:
	Atomic<int64> _ActorKey = 0;

private:
	map<int64, UserRef> _Users;
	map<int64, MonsterRef> _Monsters; 
};

extern shared_ptr<World> GWorld;