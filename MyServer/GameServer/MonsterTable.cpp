#include "pch.h"
#include "MonsterTable.h"
#include "CSVReader.h"


void MonsterTable::Init(string path)
{
	CSVReader reader;
	reader.ReadFile(path);

	for (int i = 1; i < reader.GetRowCount(); ++i)
	{
		MonsterTableData tableData;
		reader.GetCellData("ID", i, tableData.TableID);
		reader.GetCellData("HP", i, tableData.HP);
		reader.GetCellData("ATK", i, tableData.ATK);
		reader.GetCellData("Exp", i, tableData.Exp);
		reader.GetCellData("Gold", i, tableData.Gold);

		Insert(tableData.TableID, tableData);
	}
}
