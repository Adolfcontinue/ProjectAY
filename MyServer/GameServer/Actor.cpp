#include "pch.h"
#include "Actor.h"

Actor::Actor()
{
	m_TransForm = std::make_shared<TransForm>();
}

Actor::~Actor()
{
	m_TransForm.reset();
}

void Actor::SetActorKey(int64 key)
{
	m_ActorKey = key;
}

void Actor::SetType(eActorType type)
{
	m_Type = type;
}

int64 Actor::GetActorKey()
{
	return m_ActorKey;
}

eActorType Actor::GetType()
{
	return m_Type;
}

std::shared_ptr<TransForm> Actor::GetTransForm()
{
	return m_TransForm;
}






