#pragma once
#include "AgentBase.h"
#include "Protocol.pb.h"
#include "Define.h"
#include "Math.h"

class TransFormAgent : public AgentBase
{
public:
	TransFormAgent(shared_ptr<class Actor> owner);
	~TransFormAgent();

public:
	void Init(float x, float y, float z , float yaw);
	void Update();
	void SetTransForm(float x, float y, float z, float yaw);
	void SetTransForm(Protocol::TransFormData* transFormData);
	void SetPosition(Vector3& pos);
	void SetPostion(float x, float y, float z);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetYaw(float yaw);
	void SetDirection(Vector3 direction);
	void SetDirection(float x, float y, float z);
	Protocol::TransFormData* GetTransForm();
	Vector3 GetPosition();
	float GetYaw();
	void AddPosition(Vector3 other);

private:
	Protocol::TransFormData* TransForm;
	Vector3 Position;
	float Yaw;
	Vector3 Direction;
};

