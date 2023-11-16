#include "pch.h"
#include "DBConnection.h"

bool DBConnection::Connect(SQLHENV henv, const WCHAR* connectionString)
{
	if (::SQLAllocHandle(SQL_HANDLE_DBC, henv, &_connection) != SQL_SUCCESS)
		return false;

	WCHAR stringBuffer[MAX_PATH] = { 0 };
	::wcscpy_s(stringBuffer, connectionString);

	WCHAR resultString[MAX_PATH] = { 0 };
	SQLSMALLINT resultStringLen = 0;

	SQLRETURN retval = ::SQLDriverConnectW(
		_connection,
		NULL,
		reinterpret_cast<SQLWCHAR*>(stringBuffer),
		_countof(stringBuffer),
		OUT reinterpret_cast<SQLWCHAR*>(resultString),
		_countof(resultString),
		OUT & resultStringLen,
		SQL_DRIVER_NOPROMPT
	);

	if (::SQLAllocHandle(SQL_HANDLE_STMT, _connection, &_statement) != SQL_SUCCESS)
		return false;

	return (retval == SQL_SUCCESS || retval == SQL_SUCCESS_WITH_INFO);
}

void DBConnection::Clear()
{
	if (_connection != SQL_NULL_HANDLE)
	{
		::SQLFreeHandle(SQL_HANDLE_DBC, _connection);
		_connection = SQL_NULL_HANDLE;
	}

	if (_statement != SQL_NULL_HANDLE)
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, _statement);
		_statement = SQL_NULL_HANDLE;
	}
}

bool DBConnection::Execute(const WCHAR* query)
{
	SQLRETURN retval = SQLExecDirectW(_statement, (SQLWCHAR*)query, SQL_NTSL);
	if (retval == SQL_SUCCESS || retval == SQL_SUCCESS_WITH_INFO)
		return true;

	return false;
}

bool DBConnection::Fetch()
{
	SQLRETURN retval = ::SQLFetch(_statement);

	switch (retval)
	{
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:
		return true;
	case SQL_NO_DATA:
		return false;
	case SQL_ERROR:
		return false;
	default:
		return true;
	}
}

int32 DBConnection::GetRowCount()
{
	SQLLEN count = 0;
	SQLRETURN retval = ::SQLRowCount(_statement, &count);
	if (retval == SQL_SUCCESS || retval == SQL_SUCCESS_WITH_INFO)
		return static_cast<int32>(retval);

	return -1;
}

void DBConnection::FreeStmt()
{
	SQLFreeStmt(_statement, SQL_UNBIND);
	SQLFreeStmt(_statement, SQL_RESET_PARAMS);
	SQLFreeStmt(_statement, SQL_CLOSE);
}

bool DBConnection::BindParameter(int32 paramIndex, bool* value, SQLLEN* index)
{
	return BindParameter(paramIndex, SQL_C_TINYINT, SQL_TINYINT, size32(bool), value, index);
}

bool DBConnection::BindParameter(int32 paramIndex, int8* value, SQLLEN* index)
{
	return BindParameter(paramIndex, SQL_C_TINYINT, SQL_TINYINT, sizeof(int8), value, index);
}

bool DBConnection::BindParameter(int32 paramIndex, int16* value, SQLLEN* index)
{
	return BindParameter(paramIndex, SQL_C_SHORT, SQL_SMALLINT, sizeof(int16), value, index);
}

bool DBConnection::BindParameter(int32 paramIndex, int32* value, SQLLEN* index)
{
	return BindParameter(paramIndex, SQL_C_LONG, SQL_INTEGER, size32(int32), value, index);
}

bool DBConnection::BindParameter(int32 paramIndex, int64* value, SQLLEN* index)
{
	return BindParameter(paramIndex, SQL_C_SBIGINT, SQL_BIGINT, size32(int32), value, index);
}

bool DBConnection::BindParameter(int32 paramIndex, const WCHAR* value, SQLLEN* index)
{
	SQLULEN size = static_cast<SQLULEN>((::wcslen(value) + 1) * 2);
	*index = SQL_NTSL;

	if (size > WVARCHAR_MAX)
		return BindParameter(paramIndex, SQL_C_WCHAR, SQL_WLONGVARCHAR, size, (SQLPOINTER)value, index);
	else
		return BindParameter(paramIndex, SQL_C_WCHAR, SQL_WVARCHAR, size, (SQLPOINTER)value, index);
}

bool DBConnection::BindCol(int32 columnIndex, bool* value, SQLLEN* index)
{
	return BindCol(columnIndex, SQL_C_TINYINT, sizeof(bool), value, index);
}

bool DBConnection::BindCol(int32 columnIndex, int8* value, SQLLEN* index)
{
	return BindCol(columnIndex, SQL_C_TINYINT, size32(int8), value, index);
}

bool DBConnection::BindCol(int32 columnIndex, int16* value, SQLLEN* index)
{
	return BindCol(columnIndex, SQL_C_SHORT, size32(int16), value, index);
}

bool DBConnection::BindCol(int32 columnIndex, int32* value, SQLLEN* index)
{
	return BindCol(columnIndex, SQL_C_LONG, size32(int32), value, index);
}

bool DBConnection::BindCol(int32 columnIndex, int64* value, SQLLEN* index)
{
	return BindCol(columnIndex, SQL_C_SBIGINT, size32(int64), value, index);
}

bool DBConnection::BindCol(int32 columnIndex, WCHAR* str, int32 size, SQLLEN* index)
{
	return BindCol(columnIndex, SQL_C_WCHAR, size, str, index);
}

bool DBConnection::BindParameter(SQLUSMALLINT paramIndex, SQLSMALLINT cType, SQLSMALLINT sqlType, SQLULEN len, SQLPOINTER ptr, SQLLEN* index)
{
	SQLRETURN retval = ::SQLBindParameter(_statement, paramIndex, SQL_PARAM_INPUT, cType, sqlType, len, 0, ptr, 0, index);
	if (retval != SQL_SUCCESS && retval != SQL_SUCCESS_WITH_INFO)
	{
		return false;
	}

	return true;
}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, SQLSMALLINT cType, SQLULEN len, SQLPOINTER value, SQLLEN* index)
{
	SQLRETURN retval = ::SQLBindCol(_statement, columnIndex, cType, value, len, index);
	if (retval != SQL_SUCCESS && retval != SQL_SUCCESS_WITH_INFO)
	{
		return false;
	}

	return true;
}
