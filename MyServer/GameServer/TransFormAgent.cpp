#include "pch.h"
#include "TransFormAgent.h"

TransFormAgent::TransFormAgent(shared_ptr<class Actor> owner) : AgentBase(owner)
{
	TransForm = new Protocol::TransFormData();
}

TransFormAgent::~TransFormAgent()
{
	delete TransForm;
}

void TransFormAgent::Init(float x, float y, float z, float yaw)
{
	SetTransForm(x, y, z, yaw);
	Position.CopyFrom(x, y, z);
	Yaw = yaw;
}

void TransFormAgent::Update()
{
	if (Direction.Size() != 0)
	{
		Vector3 dir = Direction * 20;
		SetYaw(Direction.RotationYaw());
		AddPosition(dir);
	}
}

void TransFormAgent::SetTransForm(float x, float y, float z, float yaw)
{
	TransForm->set_x(x);
	TransForm->set_y(y);
	TransForm->set_z(z);
	TransForm->set_yaw(yaw);
	Position.CopyFrom(x, y, z);
	Yaw = yaw;
}

void TransFormAgent::SetTransForm(Protocol::TransFormData* transFormData)
{
	TransForm->CopyFrom(*transFormData);
	Position.CopyFrom(*transFormData);
	Yaw = transFormData->yaw();
}

void TransFormAgent::SetPosition(Vector3& pos)
{
}

void TransFormAgent::SetPostion(float x, float y, float z)
{
}

void TransFormAgent::SetX(float x)
{
	TransForm->set_x(x);
	Position.X = x;
}

void TransFormAgent::SetY(float y)
{
	TransForm->set_y(y);
	Position.Y = y;
}

void TransFormAgent::SetZ(float z)
{
	TransForm->set_z(z);
	Position.Z = z;
}

void TransFormAgent::SetYaw(float yaw)
{
	TransForm->set_yaw(yaw);
	Yaw = yaw;
}

void TransFormAgent::SetDirection(Vector3 direction)
{
	Direction = direction;
}

void TransFormAgent::SetDirection(float x, float y, float z)
{
	Direction.X = x;
	Direction.Y = y;
	Direction.Z = z;
}

Protocol::TransFormData* TransFormAgent::GetTransForm()
{
	return TransForm;
}

Vector3 TransFormAgent::GetPosition()
{
	return Position;
}

float TransFormAgent::GetYaw()
{
	return 0.0f;
}

void TransFormAgent::AddPosition(Vector3 other)
{
	Position += other;
	SetTransForm(Position.X, Position.Y, Position.Z, Yaw);
}

