#pragma once
#include "JobQueue.h"

class World : public JobQueue
{
public:
	void EnterUser(UserRef user);
	void LeaveUser(UserRef user);
	void BroadCast(SendBufferRef sendBuffer);
	

private:
	map<int64, UserRef> _users;
	map<int64, MonsterRef> _monsters;
};

extern shared_ptr<World> GWorld;