#pragma once
#include "Actor.h"

class Monster : public Actor
{
public:
	Monster();
	~Monster();

public:
	void SetMonsterType(eMonsterType type) { MonsterType = type; }
	void SetMonsterAbils();
	void TakeDamage(uint64 attacker, double damageAmount);
	

public:
	void Update();

private:
	//::todo world
	eMonsterType MonsterType;
	double MaxHealth;
	double Health;
	double Power;
};



