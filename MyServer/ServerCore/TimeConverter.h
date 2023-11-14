#pragma once
#include <Time.h>

class TimeConverter
{
public:
	static uint64 CurTime() { return time(NULL); }
	static uint64 DateTimeToTimeStamp(tm& datetime) { return mktime(&datetime); }
	
	static uint64 AddSeconds(int second, uint64 src = -1)
	{
		if (src == -1)	src = CurTime();
		return src + (second);
	}

	static uint64 AddMinutes(int min, uint64 src = -1)
	{
		if (src == -1)	src = CurTime();
		return AddSeconds(min * 60, src);
	}

	static uint64 AddHour(int hour, uint64 src = -1)
	{

	}

	


};

