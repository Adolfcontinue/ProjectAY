#pragma once
#include "Actor.h"

class Monster : public Actor
{
public:
	Monster();
	~Monster();

public:
	void SetMonsterType(eMonsterType type) { MonsterType = type; }

public:
	void Update();

private:
	eMonsterType MonsterType;
	//::todo world
};



