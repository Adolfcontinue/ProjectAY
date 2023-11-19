#pragma once
#include "Enum.h"

class Actor
{
public:
	Actor() {}
	virtual ~Actor();

public:
	inline void SetActorKey(int64 key) { _actorKey = key; }
	inline int64 GetActorKey() { return _actorKey; }
	inline void SetActorType(ActorType type) { _type = type; }
	inline ActorType GetActorType() { return _type; }

protected:
	int64 _actorKey;
	ActorType _type;
};

