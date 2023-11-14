#pragma once
#include <Time.h>

class TimeConverter
{
public:
	static uint64 CurTime() { return time(NULL); }
	static uint64 DateTimeToTimeStamp(tm& datetime) { return mktime(&datetime); }
	static tm TimeStampToDateTime(uint64 src)
	{
		struct tm retval;
		time_t srcval = static_cast<time_t>(src);
		gmtime_s(&retval, &srcval);
		return retval;
	}

	static bool IsExpired(uint64 src) { return src < CurTime(); }


	static uint64 AddSeconds(int second, uint64 src = -1)
	{
		if (src == -1)	src = CurTime();
		return src + (second);
	}

	static uint64 AddMinutes(int min, uint64 src = -1)
	{
		return AddSeconds(min * 60, src);
	}

	static uint64 AddHours(int hour, uint64 src = -1)
	{
		return AddMinutes(hour * 60, src);
	}

	static uint64 AddDays(int day, uint64 src = -1)
	{
		return AddHours(day * 24, src);
	}

	
};

