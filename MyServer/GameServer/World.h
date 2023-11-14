#pragma once
class World
{
public:
	void Enter(UserRef user);
	void Leave(UserRef user);
	void BroadCast(SendBufferRef sendBuffer);
	
private:
	USE_LOCK;
	map<int64, UserRef> _users;
};

