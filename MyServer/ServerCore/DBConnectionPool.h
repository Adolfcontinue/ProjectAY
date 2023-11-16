#pragma once
#include "Singleton.h"
#include "DBConnection.h"

class DBConnectionPool : public Singleton<DBConnectionPool>
{
public:
	DBConnectionPool();
	~DBConnectionPool();

public:
	virtual void Init() override;

	bool Connect(int32 connectionCount, const WCHAR* connectionString);
	void Clear();

	DBConnection* Rent();
	void Return(DBConnection* connection);

private:
	USE_LOCK;
	SQLHENV					_environment = SQL_NULL_HANDLE;
	Vector<DBConnection*>	_connections;
};

