#pragma once
#include "Singleton.h"
#include "DBQuery.h"

class QueryRunManager : public Singleton<QueryRunManager>
{
public:
	QueryRunManager();
	~QueryRunManager();

public:
	virtual void Init() override;

public:
	void Stop();
	void Push(DBQueryRef query);
	void Run();
	void Complete();
	
public:
	bool IsRun() { return run; }

private:
	USE_LOCK;
	bool run = false;
	queue<DBQueryRef> _inputQueue;
	queue<DBQueryRef> _outputQueue;
};

