#pragma once

#include <thread>
#include <functional>
#include "Singleton.h"

/*------------------
	ThreadManager
-------------------*/

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

public:
	void	Launch(function<void(void)> callback);
	void	Join();

	static void InitTLS();
	static void DestroyTLS();

	static void DoGlobalQueueWork();
	static void DistributeReserveJobs();

private:
	Mutex			_lock;
	vector<thread>	_threads;
};

