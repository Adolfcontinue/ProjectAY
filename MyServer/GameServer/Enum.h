#pragma once

enum class eActorType
{
	User,
	Monster
};


enum eAnimState
{
	Idle = 0,
	Attack1 = 2,
	Attack2 = 3,
	Move = 4,
	Dead = 5
};

enum eMonsterType
{
	Beholder,
	BlackKnight,
	Chest,
	Crab,
	Demon,
	Lizard
};