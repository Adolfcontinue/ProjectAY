#include "pch.h"
#include "AIAgent.h"
#include "Actor.h"
#include "Monster.h"
#include "World.h"
#include "User.h"
#include "TransFormAgent.h"
#include "Random.h"
#include "PathFinder.h"

AIAgent::AIAgent(shared_ptr<Actor> owner) : AgentBase(owner)
{
	TargetPosition = Vector3(0);
}

void AIAgent::Init(Protocol::ActorState state)
{
	State = state;
}

void AIAgent::Update()
{
	MonsterRef ownerMonster = static_pointer_cast<Monster>(Owner.lock());
	if (ownerMonster == nullptr)
		return;

	if (ownerMonster->GetType() != eActorType::Monster)
		return;

	UpdateFSM();

	switch (State)
	{
	case Protocol::IDlE:
		UpdateIDLE();
		break;
	case Protocol::ATTACK1:
		UpdateAttack();
		break;
	case Protocol::HIT:
		UpdateHit();
		break;
	case Protocol::MOVE:
		UpdateMove();
		break;
	case Protocol::DEAD:
		break;
	default:
		break;
	}
}

bool AIAgent::IsVaildTarget()
{
	if (TargetKey < 0)
		return false;

	UserRef target = GWorld->FindUser(TargetKey);
	if (target == nullptr)
	{
		TargetKey = -1;
		TargetPosition.Clear();
		return false;
	}

	TargetPosition = target->GetTransFormAgent()->GetPosition();
	return true;
}

bool AIAgent::CheckTargetDistance(int distance)
{
	ActorRef ownerActor = Owner.lock();
	Vector3 pos = ownerActor->GetTransFormAgent()->GetPosition();
	pos.Z = 0;
	Vector3 targetPos = TargetPosition;
	targetPos.Z = 0;
	Vector3 direction = targetPos - pos;
	if (direction.Size() > distance)
		return true;
		
	return false;
}

void AIAgent::UpdateIDLE()
{
	Owner.lock()->MoveStop();
	//sendpacket;
}

void AIAgent::UpdateMove()
{
	ActorRef ownerActor = Owner.lock();
	Vector3 pos = ownerActor->GetTransFormAgent()->GetPosition();
	if (!IsVaildTarget())
	{
		int randVal = Random::GetRandom(0, 10);
		TargetPosition = pos;
		if (randVal <= 5)
			TargetPosition.X += 100;
		else
			TargetPosition.Y += 100;
	}
	
	PathFinder finder;
	
	Vector3 targetPos = finder.FindTargetPos(pos, TargetPosition, GWorld->GetGridMap());
	pos.Z = 0;
	targetPos.Z = 0;
	Vector3 direction = targetPos - pos;
	Vector3 normalDirection = direction.Normalize();
	ownerActor->SetDirection(normalDirection);
}

void AIAgent::UpdateAttack()
{
	Owner.lock()->MoveStop();

	//sendpacket;
}

void AIAgent::UpdateHit()
{
	Owner.lock()->MoveStop();

	//sendpacket;

}

void AIAgent::UpdateFSM()
{
	if (IsVaildTarget())
	{
		switch (State)
		{
		case Protocol::IDlE:
		{
			SetState(Protocol::ActorState::ATTACK1);
			//if (CheckTargetDistance(200))
			//	SetState(Protocol::ActorState::MOVE);
			//else
			//	
		}
		break;
		case Protocol::ATTACK1:
			SetState(Protocol::ActorState::IDlE);
			break;
		case Protocol::HIT:
			SetState(Protocol::ActorState::IDlE);
			break;
		case Protocol::MOVE:
		{
			if (CheckTargetDistance(200))
				SetState(Protocol::ActorState::MOVE);
			else
				SetState(Protocol::ActorState::IDlE);
		}
		break;
		case Protocol::DEAD:
			break;
		default:
			break;
		}
	}
	else
	{
		switch (State)
		{
		case Protocol::IDlE:
			SetState(Protocol::ActorState::IDlE);
			break;
		case Protocol::ATTACK1:
			SetState(Protocol::ActorState::IDlE);
			break;
		case Protocol::HIT:
			SetState(Protocol::ActorState::IDlE);
			break;
		case Protocol::MOVE:
			SetState(Protocol::ActorState::IDlE);
			break;
		case Protocol::DEAD:
			SetState(Protocol::ActorState::IDlE);
			break;
		default:
			break;
		}
	}
}

void AIAgent::SetTarget(uint64 target)
{
	TargetKey = target;
}

void AIAgent::SetState(Protocol::ActorState state)
{
	State = state;
}

Protocol::ActorState AIAgent::GetState()
{
	return State;
}

Vector3 AIAgent::GetTargerPosition()
{
	return TargetPosition;
}





