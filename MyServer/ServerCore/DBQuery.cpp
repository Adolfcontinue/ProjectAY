#include "pch.h"
#include "DBQuery.h"

DBQuerySample::DBQuerySample(int64 sessionKey,int32 param1, int32 param2) : _sessionKey(sessionKey)
{
	_inputData.param1 = param1;
	_inputData.param2 = param2;
}

void DBQuerySample::Run()
{
	DBConect;

	int inputIndex = 0;
	SQLLEN input;
	con->BindParameter(inputIndex++, &_inputData.param1, &input);
}

void DBQuerySample::Complete()
{
	//nothing
}
