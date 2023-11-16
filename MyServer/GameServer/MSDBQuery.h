#pragma once
#include "DBQuery.h"

class MsDBQuery
{
};

class QueryLogin : public DBQuery
{
public:
	QueryLogin(int64 sessionKey, int32 param1, int32 param2);

	struct InData
	{
		int32 param1;
		int32 param2;
	};

	struct OutData
	{
		int32 outval1;
		int32 outval2;
	};

public:
	virtual void Run() override;
	virtual void Complete() override;

private:
	long _sessionKey;
	InData _inputData;
	OutData _outputData;
};

