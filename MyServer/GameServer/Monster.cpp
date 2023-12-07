#include "pch.h"
#include "Monster.h"
#include "World.h"

Monster::Monster()
{
}

Monster::~Monster()
{
	shared_from_this();
}

void Monster::Update()
{
	//::todo monster fsm
	//GWorld->BroadCast()
}
