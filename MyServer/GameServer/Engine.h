#pragma once
#include "DBConnectionPool.h"
#include "ThreadManager.h"
#include "QueryRunManager.h"

class Engine
{
public:
	Engine()
	{
		DBConnectionPool::Instance().Init();
		ThreadManager::Instance().Init();
		SendBufferManager::Instance().Init();
		QueryRunManager::Instance().Init();
	}

	~Engine()
	{
		DBConnectionPool::Destroy();
		ThreadManager::Destroy();
		SendBufferManager::Destroy();
		QueryRunManager::Destroy();
	}
} GEngine;

