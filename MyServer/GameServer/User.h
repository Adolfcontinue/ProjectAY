#pragma once
#include "Actor.h"
#include "TransFormAgent.h"
#include "StatusAgent.h"

class User : public Actor
{
public:
	User();
	User(string id, string pw, int64 sessionKey, int32 level, int32 exp);
	~User() {};

public:
	void Init(int64 sessionKey, string id, string pw, float x, float y , float z ,float yaw, int64 level, int64 exp, float dmg, float maxhp);
	void SetID(string id) { _Id = id; };
	void SetPW(string pw) { _Pw = pw; };
	void SetSessionKey(int64 sessionKey) { _SessionKey = sessionKey; };
	void SetLevel(int32 level) { _Level = level; };
	void SetExp(int32 exp) { _Exp = exp; }

	string GetID() { return _Id; }
	string GetPW() { return _Pw; }
	int64 GetSessionKey() { return _SessionKey; }
	int32 GetLevel() { return _Level; }
	int32 GetExp() { return _Exp; }
	void ReqWorldData();

	std::shared_ptr<StatusAgent> GetStatus();

private:
	int64 _SessionKey;
	string _Id;
	string _Pw;
	int32 _Level;
	int32 _Exp;

	std::shared_ptr<StatusAgent> Status;
};

