#include "pch.h"
#include "AgentBase.h"
#include "Actor.h"

AgentBase::AgentBase(weak_ptr<Actor> owner)
{
	Owner = owner;
}

shared_ptr<Actor> AgentBase::GetOwner()
{
	return Owner.lock();
}
