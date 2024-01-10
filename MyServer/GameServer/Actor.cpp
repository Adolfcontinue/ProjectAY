#include "pch.h"
#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::SetPosition(Float3 pos)
{
	Position.X = pos.X;
	Position.Y = pos.Y;
	Position.Z = pos.Z;
}

void Actor::SetPosition(double x, double y, double z)
{
	Position.X = x;
	Position.Y = y;
	Position.Z = z;
}

void Actor::SetRotation(Float4 rot)
{
	Rotation.X = rot.X;
	Rotation.Y = rot.Y;
	Rotation.Z = rot.Z;
	Rotation.W = rot.W;
}

void Actor::SetRotation(double x, double y, double z, double w)
{
	Rotation.X = x;
	Rotation.Y = y;
	Rotation.Z = z;
	Rotation.W = w;
}



