#include "pch.h"
#include "ConsoleLogger.h"

string ConsoleLog::ConvertString()
{
	return _msg;
}

void ConsoleLogger::SetLogType(ConsoleLogType type)
{
	_type = type;
}

void ConsoleLogger::AddLog(ConsoleLog* log)
{
	WRITE_LOCK;
	_logqueue.push(log);
}

void ConsoleLogger::Print()
{
	WRITE_LOCK;
	while (!_logqueue.empty())
	{
		ConsoleLog* data = _logqueue.front();
		cout << data->ConvertString() << std::endl;
		_logqueue.pop();
		delete data;
	}
}

