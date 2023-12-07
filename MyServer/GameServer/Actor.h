#pragma once
#include "Enum.h"
#include "Float3.h"

class Actor : public JobQueue
{
public:
	Actor();
	virtual ~Actor();

public:
	inline void SetActorKey(int64 key) { _ActorKey = key; }
	inline int64 GetActorKey() { return _ActorKey; }
	
public:
	inline void SetPos(std::shared_ptr<Float3> pos) { _Pos = pos; }
	inline void SetPosX(double x) { _Pos->_x = x; }
	inline void SetPosY(double y) { _Pos->_y = y; }
	inline void SetPosZ(double z) { _Pos->_z = z; }
	inline void SetType(ActorType type) { _Type = type; }

	inline Float3* GetPos() { return _Pos.get(); }
	inline double GetPosX() { return _Pos->_x; }
	inline double GetPosY() { return _Pos->_y; }
	inline double GetPosZ() { return _Pos->_z; }
	inline ActorType GetType() { return _Type; }

protected:
	int64 _ActorKey;
	std::shared_ptr<Float3> _Pos;
	ActorType _Type;
};

