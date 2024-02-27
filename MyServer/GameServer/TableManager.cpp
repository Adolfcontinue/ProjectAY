#include "pch.h"
#include <filesystem>
#include <iostream>
#include "TableManager.h"
#include "MonsterTable.h"
#include "DefineTable.h"
#include "LevelTable.h"

namespace fs = std::filesystem;

TableManager::TableManager()
{
	//Tables.insert(make_pair("MonsterTable", std::static_pointer_cast<TableBase>(m_MonsterTable)));
	m_MonsterTable = make_shared<MonsterTable>();
	m_DefineTable = make_shared<DefineTable>();
	m_LevelTable = make_shared<LevelTable>();
}

TableManager::~TableManager()
{
}

void TableManager::Init()
{
	m_MonsterTable->Init(GetPath("MonsterTable.csv"));
	m_DefineTable->Init(GetPath("DefineTable.csv"));
	m_LevelTable->Init(GetPath("LevelTable.csv"));
}

MonsterTableData TableManager::GetMonsterTableData(int tableID) const
{
	return m_MonsterTable->Find(tableID);
}

DefineTableData TableManager::GetDefineTableData(string tableID) const
{
	return m_DefineTable->Find(tableID);
}

LevelTableData TableManager::GetLevelTableData(int tableID) const
{
	return m_LevelTable->Find(tableID);
}

std::string TableManager::GetPath(std::string tableName)
{
	fs::path p(".././Table");
	auto path = fs::canonical(p);
	path = path / tableName;
	return path.string();
}


