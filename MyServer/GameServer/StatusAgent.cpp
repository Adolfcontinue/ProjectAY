#include "pch.h"
#include "StatusAgent.h"
#include "Actor.h"

StatusAgent::StatusAgent(shared_ptr<Actor> owner) : AgentBase(owner)
{

}

void StatusAgent::Init(int64 level, int64 exp, float dmg, float maxHP)
{
	SetLevel(level);
	SetExp(exp);
	SetDmg(dmg);
	SetMaxHP(maxHP);
}

void StatusAgent::SetLevel(int64 level)
{
	Level = level;
}

void StatusAgent::SetExp(int64 exp)
{
	Exp = exp;
}

void StatusAgent::SetDmg(float dmg)
{
	Damage = dmg;
}

void StatusAgent::SetMaxHP(float maxHP)
{
	SetHP(maxHP);
}

void StatusAgent::SetHP(float hp)
{
	HP = hp;
}

int64 StatusAgent::GetLevel()
{
	return Level;
}

int64 StatusAgent::GetExp()
{
	return Exp;
}

float StatusAgent::GetDmg()
{
	return Damage;
}

float StatusAgent::GetMaxHP()
{
	return MaxHP;
}

float StatusAgent::GetHP()
{
	return HP;
}

void StatusAgent::TakeDamage(float dmg)
{
	HP -= dmg;
}
