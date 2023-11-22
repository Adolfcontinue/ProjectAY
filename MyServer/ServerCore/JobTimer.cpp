#include "pch.h"
#include "JobTimer.h"
#include "JobQueue.h"

void JobTimer::Reserve(uint64 tickAfter, weak_ptr<JobQueue> owner, JobRef job)
{
	const uint64 executeTick = GetTickCount64() + tickAfter;
	JobData* jobData = ObjectPool<JobData>::Pop(owner, job);

	WRITE_LOCK;
	_Items.push(TimerItem{ executeTick, jobData });
}

void JobTimer::Distribute(uint64 now)
{
	if (_Distributing.exchange(true) == false)
		return;

	Vector<TimerItem> items;

	{
		WRITE_LOCK;
		while (_Items.empty() == false)
		{
			const TimerItem& timeritem = _Items.top();
			if (now < timeritem.ExecuteTick)
				break;

			items.push_back(timeritem);
			_Items.pop();
		}
	}

	for (TimerItem& item : items)
	{
		if (JobQueueRef owner = item.JobData->Owner.lock())
			owner->Push(item.JobData->Job);

		ObjectPool<JobData>::Push(item.JobData);
	}

	_Distributing.store(false);
}

void JobTimer::Clear()
{
	WRITE_LOCK;

	while (_Items.empty() == false)
	{
		const TimerItem& timerItem = _Items.top();
		ObjectPool<JobData>::Push(timerItem.JobData);
		_Items.pop();
	}
}
