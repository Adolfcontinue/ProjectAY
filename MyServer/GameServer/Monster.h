#pragma once
#include "Actor.h"
#include "TransFormAgent.h"
#include "AIAgent.h"

class Monster : public Actor
{
public:
	Monster();
	~Monster();

public:
	void Init(int64 actorKey, eMonsterType monsterType, float x, float y, float z, float yaw);
	void SetMonsterType(eMonsterType type) { MonsterType = type; }
	void SetMonsterAbils();
	void TakeDamage(uint64 attacker, float damageAmount);

public:
	void Update();

private:
	//::todo world
	eMonsterType MonsterType;
	double MaxHealth;
	double Health;
	double Power;
	uint64 TargetKey;
	std::shared_ptr<AIAgent> m_AI; 
};



