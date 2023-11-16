#include "pch.h"
#include "MsDBQuery.h"


QueryLogin::QueryLogin(int64 sessionKey, int32 param1, int32 param2)
{
	_inputData.param1 = param1;
	_inputData.param2 = param2;
}

void QueryLogin::Run()
{
	DBConect;
	if (con == nullptr)
		return;

	int inputIndex = 0;
	SQLLEN input;
	con->BindParameter(inputIndex++, &_inputData.param1, &input);
}

void QueryLogin::Complete()
{
	//nothing
}
