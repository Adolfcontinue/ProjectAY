#pragma once

class AgentBase : public JobQueue
{
public:
	AgentBase(weak_ptr<class Actor> owner);
	shared_ptr<Actor> GetOwner();

protected:
	weak_ptr<class Actor> Owner;
};

