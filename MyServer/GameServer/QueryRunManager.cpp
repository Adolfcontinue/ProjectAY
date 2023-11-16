#include "pch.h"
#include "QueryRunManager.h"

QueryRunManager::QueryRunManager() : run(true)
{
}

QueryRunManager::~QueryRunManager()
{

}

void QueryRunManager::Init()
{
	if(!IsRun())
		run = true;
}

void QueryRunManager::Stop()
{
	WRITE_LOCK;

	run = false;
	while (!_inputQueue.empty())
	{
		_inputQueue.pop();
	}
	_inputQueue = queue<DBQueryRef>();

	while (!_outputQueue.empty())
	{
		_outputQueue.pop();
	}
	_outputQueue = queue<DBQueryRef>();
}

void QueryRunManager::Push(DBQueryRef query)
{
	WRITE_LOCK;
	_inputQueue.push(query);
}

void QueryRunManager::Run()
{
	WRITE_LOCK;
	while (run && !_inputQueue.empty())
	{
		DBQueryRef query = _inputQueue.front();
		query->Run();

		_outputQueue.push(query);
		_inputQueue.pop();
	}
}

void QueryRunManager::Complete()
{
	WRITE_LOCK;
	while (run && !_outputQueue.empty())
	{
		DBQueryRef query = _outputQueue.front();
		query->Complete();

		_outputQueue.pop();
	}
}
