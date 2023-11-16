#pragma once
#include <sql.h>
#include <sqlext.h>

enum
{
	WVARCHAR_MAX = 4000
};

class DBConnection
{
public:
	bool Connect(SQLHENV henv, const WCHAR* connectionString);
	void Clear();
	bool Execute(const WCHAR* query);
	bool Fetch();
	int32 GetRowCount();
	void FreeStmt();

public:
	bool BindParameter(int32 paramIndex, bool* value, SQLLEN* index);
	bool BindParameter(int32 paramIndex, int8* value, SQLLEN* index);
	bool BindParameter(int32 paramIndex, int16* value, SQLLEN* index);
	bool BindParameter(int32 paramIndex, int32* value, SQLLEN* index);
	bool BindParameter(int32 paramIndex, int64* value, SQLLEN* index);
	bool BindParameter(int32 paramIndex, const WCHAR* value, SQLLEN* index);


	bool BindCol(int32 columnIndex, bool* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int8* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int16* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int32* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int64* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, WCHAR* str, int32 size, SQLLEN* index);

private:
	bool BindParameter(SQLUSMALLINT paramIndex, SQLSMALLINT cType, SQLSMALLINT sqlType, SQLULEN len, SQLPOINTER ptr, SQLLEN* index);
	bool BindCol(SQLUSMALLINT columnIndex, SQLSMALLINT cType, SQLULEN len, SQLPOINTER value, SQLLEN* index);

private:
	SQLHDBC _connection = SQL_NULL_HANDLE;
	SQLHSTMT _statement = SQL_NULL_HANDLE;
};

