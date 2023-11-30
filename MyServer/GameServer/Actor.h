#pragma once
#include "Enum.h"

class Actor : public JobQueue
{
public:
	Actor() {}
	virtual ~Actor();

public:
	inline void SetActorKey(int64 key) { _ActorKey = key; }
	inline int64 GetActorKey() { return _ActorKey; }
	
protected:
	int64 _ActorKey;
};

