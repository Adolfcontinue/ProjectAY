#pragma once

#include "Singleton.h"

class ConsoleLogger : Singleton<ConsoleLogger>
{
public:
	ConsoleLogger();
	~ConsoleLogger();

public:
	virtual void Init() override;

public:
	void Run() { run = true; }
	void Stop() { run = false; };

public:
	USE_LOCK;
	void AddLog(string log);
	void Print();

private:
	bool run = false;
	Queue<string> log_queue;
};


