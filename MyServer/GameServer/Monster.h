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
	void SetTarget(uint64 target);

public:
	void Update();

private:
	bool IsVaildTarget();
	void LookAt(Float3 pos);

private:
	//::todo world
	eMonsterType MonsterType;
	double MaxHealth;
	double Health;
	double Power;

	uint64 TargetKey;
};



