#pragma once

template<typename TKey>
struct TableData
{
public:
	TKey TableID;
};


struct MonsterTableData : public TableData<int>
{
	MonsterTableData() : HP(-1), ATK(-1), Exp(-1), Gold(-1) {}
public:
	int32 HP;
	int32 ATK;
	int32 Exp;
	int32 Gold;
};

struct DefineTableData : public TableData<string>
{
	DefineTableData() : int32Value(-1), floatValue(-1.f), doubleValue(-1.0), strValue("") {}
public:
	int32 int32Value;
	float floatValue;
	double doubleValue;
	string strValue;
};


struct LevelTableData : public TableData<int>
{
	LevelTableData() : Level(-1), HP(-1), ATK(-1), UpExp(-1) {}
public:
	int32 Level;
	int32 HP;
	int32 ATK;
	int32 UpExp;
};
