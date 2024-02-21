#pragma once
#include "Define.h"
#include "JobQueue.h"
#include "Protocol.pb.h"
#include "GridMap.h"

using GridMapRef = std::shared_ptr<class GridMap>;

class World : public JobQueue
{
	friend class User;


private:
	Atomic<int64> _ActorKey = 0;
	map<int64, UserRef> _Users;
	map<int64, MonsterRef> _Monsters;
	GridMap* Map;

public:
	void Init();
	void EnterUser(UserRef user);
	void LeaveUser(int64 sessionKey);
	void BroadCast(SendBufferRef sendBuffer);
	void BroadCastExcept(SendBufferRef sendBuffer, int64 exceptKey);
	UserRef FindUser(int64 key);
	//void MoveUser(int64 sessionKey, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT4 rot, Protocol::ActorState playerState);
	void MoveUser(int64 sessionKey, Protocol::TransFormData transform, Protocol::ActorState state);
	MonsterRef FindMonster(uint64 key);
	GridMap* GetGridMap();


public:
	void CreateMonster();

public:
	void Update();

private:
	int64 IssueActorKey() { return _ActorKey.fetch_add(1); }

};

extern shared_ptr<World> GWorld;