#pragma once
#include "Enum.h"
#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"
#include "TransForm.h"

class Actor : public JobQueue
{
public:
	Actor();
	virtual ~Actor();

public:
	void SetActorKey(int64 key);
	void SetType(eActorType type);
	int64 GetActorKey();
	eActorType GetType();
	std::shared_ptr<TransForm> GetTransForm();

protected:
	int64	m_ActorKey;
	eActorType m_Type;
	std::shared_ptr<TransForm> m_TransForm;
};

