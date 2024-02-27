#pragma once
#include "Table.h"
#include "TableData.h"

class DefineTable : public Table<string, DefineTableData>
{
public:
	virtual void Init(string path = "") override;
};
