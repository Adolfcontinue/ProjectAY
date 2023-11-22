#pragma once

struct JobData
{
	JobData(weak_ptr<JobQueue> owner, JobRef job) : Owner(owner), Job(job)
	{

	}


	weak_ptr<JobQueue> Owner;
	JobRef Job;
};

struct TimerItem
{
	bool operator<(const TimerItem& other) const
	{
		return ExecuteTick > other.ExecuteTick;
	}


	uint64 ExecuteTick = 0;
	JobData* JobData = nullptr;
};

class JobTimer
{
public:
	void Reserve(uint64 tickAfter, weak_ptr<JobQueue> owner, JobRef job);
	void Distribute(uint64 now);
	void Clear();


private:
	USE_LOCK;
	PriorityQueue<TimerItem> _Items;
	Atomic<bool> _Distributing = false;
};

