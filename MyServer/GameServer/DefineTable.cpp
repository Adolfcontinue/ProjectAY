#include "pch.h"
#include "DefineTable.h"
#include "CSVReader.h"


void DefineTable::Init(string path)
{
	CSVReader reader;
	reader.ReadFile(path);

	for (int i = 1; i < reader.GetRowCount(); ++i)
	{
		DefineTableData tableData;
		reader.GetCellData("ID", i, tableData.TableID);
		reader.GetCellData("int32Val", i, tableData.int32Value);
		reader.GetCellData("floatVal", i, tableData.floatValue);
		reader.GetCellData("doubleVal", i, tableData.doubleValue);
		reader.GetCellData("strVal", i, tableData.strValue);

		Insert(tableData.TableID, tableData);
	}
}
