#pragma once

enum class ActorType
{
	User,
	Monster
};


enum AnimState
{
	Idle = 0,
	Attack1 = 2,
	Attack2 = 3,
	Move = 4,
	Dead = 5
};