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
	void SetPos(Float3 pos);
	void SetPos(double x, double y, double z);
	inline void SetPosX(double x) { _Pos._x = x; }
	inline void SetPosY(double y) { _Pos._y = y; }
	inline void SetPosZ(double z) { _Pos._z = z; }
	
	void SetRot(Float3 rot);
	void SetRot(double x, double y, double z);
	inline void SetRotX(double x) { _Rot._x = x; }
	inline void SetRotY(double y) { _Rot._y = y; }
	inline void SetRotZ(double z) { _Rot._z = z; }
	inline void SetType(ActorType type) { _Type = type; }

	inline Float3 GetPos() { return _Pos; }
	inline double GetPosX() { return _Pos._x; }
	inline double GetPosY() { return _Pos._y; }
	inline double GetPosZ() { return _Pos._z; }
	inline Float3 GetRot() { return _Rot; }
	inline double GetRotX() { return _Rot._x; }
	inline double GetRotY() { return _Rot._y; }
	inline double GetRotZ() { return _Rot._z; }
	inline ActorType GetType() { return _Type; }


protected:
	int64 _ActorKey;
	Float3 _Pos;
	Float3 _Rot;
	ActorType _Type;
};

