#include "pch.h"
#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::SetPos(Float3 pos)
{
	_Pos._x = pos._x;
	_Pos._y = pos._y;
	_Pos._z = pos._z;
}

void Actor::SetPos(double x, double y, double z)
{
	_Pos._x = x;
	_Pos._y = y;
	_Pos._z = z;
}

void Actor::SetRot(Float3 rot)
{
	_Rot._x = rot._x;
	_Rot._y = rot._y;
	_Rot._z = rot._z;
}

void Actor::SetRot(double x, double y, double z)
{
	_Rot._x = x;
	_Rot._y = y;
	_Rot._z = z;
}

