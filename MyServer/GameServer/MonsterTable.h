#pragma once
#include "Table.h"
#include "TableData.h"

class MonsterTable : public Table<int, MonsterTableData>
{
public:
	virtual void Init(string path = "") override;
};

