#include "pch.h"
#include "LevelTable.h"
#include "CSVReader.h"

void LevelTable::Init(string path)
{
	CSVReader reader;
	reader.ReadFile(path);

	for (int i = 1; i < reader.GetRowCount(); ++i)
	{
		LevelTableData tableData;
		reader.GetCellData("ID", i, tableData.TableID);
		reader.GetCellData("Level", i, tableData.Level);
		reader.GetCellData("HP", i, tableData.HP);
		reader.GetCellData("ATK", i, tableData.ATK);
		reader.GetCellData("UpExp", i, tableData.UpExp);
		
		Insert(tableData.TableID, tableData);
	}
}
