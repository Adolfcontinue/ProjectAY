#pragma once
#include "Table.h"
#include "TableData.h"

class LevelTable : public Table<int, LevelTableData>
{
public:
	virtual void Init(string path = "") override;
};

