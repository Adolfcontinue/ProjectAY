#pragma once
class User : public enable_shared_from_this<User>
{
public:
	User() {};
	~User() {};

public:
	void SetID(string id) { _id = id; };
	void SetPW(string pw) { _pw = pw; };
	void SetSessionKey(int64 sessionKey) { _sessionKey = sessionKey; };
	void SetLevel(int32 level) { _level = level; };
	void SetExp(int32 exp) { _exp = exp; }

	string GetID() { return _id; }
	string GetPW() { return _pw; }
	int64 GetSessionKey() { return _sessionKey; }
	int32 GetLevel() { return _level; }
	int32 GetExp() { return _exp; }
	
private:
	string _id;
	string _pw;
	int64 _sessionKey;

	int32 _level;
	int32 _exp;
};

