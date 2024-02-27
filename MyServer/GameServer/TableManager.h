#pragma once
#include "Singleton.h"
#include "TableData.h"

class TableManager : public Singleton<TableManager>
{
public:
	TableManager();
	~TableManager();
	
private:
	//map<string, std::shared_ptr<class TableBase>> Tables;
	std::shared_ptr<class MonsterTable> m_MonsterTable;
	std::shared_ptr<class DefineTable> m_DefineTable;
	std::shared_ptr<class LevelTable> m_LevelTable;

public:
	virtual void Init() override;
	MonsterTableData GetMonsterTableData(int tableID) const;
	DefineTableData GetDefineTableData(string tableID) const;
	LevelTableData GetLevelTableData(int tableID) const;
	
	//template<typename TableData, typename TableType, typename KeyType>
	//TableData GetTableData(string tableName, KeyType tableKey)
	//{
	//	auto iter = Tables.find(tableName);
	//	if (iter == Tables.end())
	//		return TableData();

	//	std::shared_ptr<TableType> findTable = std::static_pointer_cast<TableType>(iter->second);
	//	return findTable->Find(tableKey);
	//}

private:
	std::string GetPath(std::string tableName);
};

