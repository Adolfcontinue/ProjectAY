#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "Memory.h"
#include "DeadLockProfiler.h"
#include "SocketUtils.h"
#include "SendBuffer.h"
#include "DBConnectionPool.h"

Memory*				GMemory = nullptr;
DeadLockProfiler*	GDeadLockProfiler = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		/*DBConnectionPool::Instance().Init();
		ThreadManager::Instance().Init();
		SendBufferManager::Instance().Init();
		QueryRunManager::Instance().Init();*/
		//GThreadManager = new ThreadManager();

		GMemory = new Memory();
		GDeadLockProfiler = new DeadLockProfiler();
		SocketUtils::Init();
	}

	~CoreGlobal()
	{
		/*ThreadManager::Destroy();
		SendBufferManager::Destroy();
		DBConnectionPool::Destroy();
		QueryRunManager::Destroy();*/

		//delete GThreadManager;
		delete GMemory;
		delete GDeadLockProfiler;
		SocketUtils::Clear();
	}
} GCoreGlobal;