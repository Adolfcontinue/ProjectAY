#include "pch.h"
#include "ConsoleLogger.h"

ConsoleLogger::ConsoleLogger()
{
}

ConsoleLogger::~ConsoleLogger()
{
}

void ConsoleLogger::Init()
{
}

void ConsoleLogger::AddLog(string log)
{
	WRITE_LOCK;
	log_queue.push(log);
}

void ConsoleLogger::Print()
{
	WRITE_LOCK;
	while (run && !log_queue.empty())
	{
		cout << log_queue.front() << std::endl;
		log_queue.pop();
	}
}

