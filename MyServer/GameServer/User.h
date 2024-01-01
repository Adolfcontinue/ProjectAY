#pragma once
#include "Float3.h"
#include "Actor.h"

class User : public Actor
{
public:
	User();
	User(string id, string pw, int64 sessionKey, int32 level, int32 exp);
	~User() {};

public:
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


private:
	int64 _SessionKey;
	string _Id;
	string _Pw;
	int32 _Level;
	int32 _Exp;

};

