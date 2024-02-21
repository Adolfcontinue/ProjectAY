#include "pch.h"
#include "Actor.h"
#include "TransFormAgent.h"

Actor::Actor() : m_ActorKey(-1), m_Type(eActorType::User), m_State(Protocol::ActorState::IDlE)
{
}

Actor::~Actor()
{
}

void Actor::SetActorKey(int64 key)
{
	m_ActorKey = key;
}

void Actor::SetType(eActorType type)
{
	m_Type = type;
}

void Actor::SetActorState(Protocol::ActorState state)
{
	m_State = state;
}

void Actor::SetDirection(Vector3 direction)
{
	TransForm->SetDirection(direction);
}

void Actor::MoveStop()
{
	TransForm->SetDirection(0, 0, 0);
}

std::shared_ptr<TransFormAgent> Actor::GetTransFormAgent()
{
	return TransForm;
}

Protocol::ActorState Actor::GetActorState()
{
	return m_State;
}

int64 Actor::GetActorKey()
{
	return m_ActorKey;
}

eActorType Actor::GetType()
{
	return m_Type;
}






