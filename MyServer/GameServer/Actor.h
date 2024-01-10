#pragma once
#include "Enum.h"
#include "Float3.h"

class Actor : public JobQueue
{
public:
	Actor();
	virtual ~Actor();

public:
	inline void SetActorKey(int64 key) { ActorKey = key; }
	inline int64 GetActorKey() { return ActorKey; }
	
public:
	void SetPosition(Float3 pos);
	void SetPosition(double x, double y, double z);
	inline void SetPosX(double x) { Position.X = x; }
	inline void SetPosY(double y) { Position.Y = y; }
	inline void SetPosZ(double z) { Position.Z = z; }
	
	void SetRotation(Float4 rot);
	void SetRotation(double x, double y, double z, double w);
	inline void SetRotationX(double x) { Rotation.X = x; }
	inline void SetRotationY(double y) { Rotation.Y = y; }
	inline void SetRotationZ(double z) { Rotation.Z = z; }
	inline void SetRotationW(double w) { Rotation.W = w; }
	inline void SetType(ActorType type) { Type = type; }

	inline Float3 GetPosition() { return Position; }
	inline double GetPositionX() { return Position.X; }
	inline double GetPositionY() { return Position.Y; }
	inline double GetPositionZ() { return Position.Z; }

	inline Float4 GetRotation() { return Rotation; }
	inline double GetRotationX() { return Rotation.X; }
	inline double GetRotationY() { return Rotation.Y; }
	inline double GetRotationZ() { return Rotation.Z; }
	inline double GetRotationW() { return Rotation.W; }

	inline ActorType GetType() { return Type; }


protected:
	int64	ActorKey;
	Float3	Position;
	Float4	Rotation;
	ActorType Type;
};

