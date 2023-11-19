#pragma once
class World
{
public:
	void EnterUser(UserRef user);
	void LeaveUser(UserRef user);
	void BroadCast(SendBufferRef sendBuffer);
	

private:
	USE_LOCK;
	map<int64, UserRef> _users;
	map<int64, MonsterRef> _monsters;
};

