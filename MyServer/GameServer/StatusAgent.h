#pragma once
#include "AgentBase.h"
class StatusAgent : public AgentBase
{
public:
	StatusAgent(shared_ptr<class Actor> owner);

public:
	void Init(int64 level, int64 exp, float dmg, float maxHP);
	void SetLevel(int64 level);
	void SetExp(int64 exp);
	void SetDmg(float dmg);
	void SetMaxHP(float maxHP);
	void SetHP(float hp);
	int64 GetLevel();
	int64 GetExp();
	float GetDmg();
	float GetMaxHP();
	float GetHP();

public:
	void TakeDamage(float dmg);


private:
	int64 Level;
	int64 Exp;
	float Damage;
	float MaxHP;
	float HP;
};

