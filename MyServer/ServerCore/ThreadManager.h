#pragma once

#include <thread>
#include <functional>
#include "Singleton.h"

/*------------------
	ThreadManager
-------------------*/

class ThreadManager	: public Singleton<ThreadManager>
{
public:
	ThreadManager();
	~ThreadManager();

public:
	virtual void Init() override;

	void	Launch(function<void(void)> callback);
	void	Join();

	static void InitTLS();
	static void DestroyTLS();

private:
	Mutex			_lock;
	vector<thread>	_threads;
};

