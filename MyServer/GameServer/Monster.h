#pragma once
#include "Actor.h"

class Monster : public Actor
{
public:
	Monster();
	~Monster();

public:
	int64 GetMonsterKey() { return _MonsterKey; }
	void SetMonsterKey(int64 key) { _MonsterKey = key; }
	void Update();



private:
	int64 _MonsterKey;

	//::todo world
};



