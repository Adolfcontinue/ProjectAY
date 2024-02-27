#pragma once
#include "Enum.h"
#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"
#include "TransForm.h"
#include "TransFormAgent.h"
#include "Math.h"

class Actor : public JobQueue
{
public:
	Actor();
	virtual ~Actor();

public:
	void SetActorKey(int64 key);
	void SetType(eActorType type);
	void SetActorState(Protocol::ActorState state);
	void SetDirection(Vector3 direction);
	void MoveStop();

	std::shared_ptr<TransFormAgent> GetTransFormAgent();
	Protocol::ActorState GetActorState();
	int64 GetActorKey();
	eActorType GetType();
	bool IsEnable();
	void Enable();


protected:
	int64	m_ActorKey;
	eActorType m_Type;
	Protocol::ActorState m_State;
	std::shared_ptr<TransFormAgent> m_TransForm;
	Vector3 m_Direction;
	bool m_Enable;
};

