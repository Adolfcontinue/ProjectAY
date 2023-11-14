#pragma once

#ifdef _DEBUG
#define TEST
#endif


enum ConsoleLogType
{
	Fatal	= 0x00001,
	Error	= 0x00010,
	Warnig	= 0x00100,
	Info	= 0x01000,
	Debug	= 0x10000
};

class ConsoleLog
{
public:
	ConsoleLog(ConsoleLogType type, string msg) : _type(type), _msg(msg) {}
	
public:
	string ConvertString();
	
private:
	ConsoleLogType _type;
	string _msg;
};


class ConsoleLogger
{
public:
	void SetLogType(ConsoleLogType type);

public:
	USE_LOCK;
	void AddLog(ConsoleLog* log);
	void Print();

private:
	ConsoleLogType _type;
	Queue<ConsoleLog*> _logqueue;
} 
GConsoleLogger;


