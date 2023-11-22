#include "pch.h"
#include "JobQueue.h"
#include "GlobalQueue.h"

void JobQueue::Push(JobRef job, bool pushOnly)
{
	const int prevCnt = _JobCount.fetch_add(1);
	_Jobs.Push(job);

	if (prevCnt == 0)
	{
		if (LCurrentJobQueue == nullptr && pushOnly == false)
		{
			Execute();
		}
		else
		{
			GGlobalQueue->Push(shared_from_this());
		}
	}
}

void JobQueue::Execute()
{
	LCurrentJobQueue = this;

	while (true)
	{
		Vector<JobRef> jobs;
		_Jobs.PopAll(jobs);

		const int32 jobCnt = static_cast<int32>(jobs.size());
		for (int32 i = 0; i < jobCnt; i++)
		{
			jobs[i]->Execute();
		}

		if (_JobCount.fetch_sub(jobCnt) == jobCnt)
		{
			LCurrentJobQueue = nullptr;
			return;
		}

		const uint64 now = GetTickCount64();
		if (now >= LEndTickCount)
		{
			LCurrentJobQueue = nullptr;
			GGlobalQueue->Push(shared_from_this());
			break;
		}
	}
}
