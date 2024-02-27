#pragma once
#include "AgentBase.h"
#include "Define.h"
#include "Protocol.pb.h"
#include "Math.h"

#define TickCount 2000

class AIAgent : public AgentBase
{
public:
	AIAgent(shared_ptr<class Actor> owenr);


public:
	void Init(Protocol::ActorState state);
	void Update ();
	void SetTarget(uint64 target);
	void SetState(Protocol::ActorState state);
	Protocol::ActorState GetState();
	Vector3 GetTargerPosition();


private:
	bool IsVaildTarget();
	bool CheckTargetDistance(int distance = 1);
	void UpdateIDLE();
	void UpdateMove();
	void UpdateAttack();
	void UpdateHit();
	void UpdateFSM();
	void UpdateDie();

private:
	Protocol::ActorState State;
	uint64 TargetKey;
	Vector3 TargetPosition;
	int64 Tick;
};

