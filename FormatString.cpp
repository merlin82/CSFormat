#include "FormatString.h"
#include <time.h>
#include <iomanip>

void _formatTime(std::ostringstream &ss, time_t t)
{
	struct tm tm1;
	char szTime[24];
#ifdef _WIN32
	localtime_s(&tm1, &t);
	sprintf_s(szTime, 24, "%04d-%02d-%02d %02d:%02d:%02d",
		tm1.tm_year + 1900, tm1.tm_mon + 1, tm1.tm_mday,
		tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
#else
	localtime_r(&t, &tm1);
	snprintf(szTime, 24, "%04d-%02d-%02d %02d:%02d:%02d",
		tm1.tm_year + 1900, tm1.tm_mon + 1, tm1.tm_mday,
		tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
#endif
	
	ss << szTime;
}

void _formatItem(std::ostringstream &ss, const std::string& item, const CArgArray& args)
{
	//{ index[,alignment][ :formatString] }
	int index = 0;
	int alignment = 0;
	std::string fmt;

	char* endptr = NULL;
	index = strtol(&item[0], &endptr, 10);
	if (index < 0 || index >= args.size())
	{
		return;
	}

	if (*endptr == ',')
	{
		alignment = strtol(endptr + 1, &endptr, 10);
		if (alignment > 0)
		{
			ss << std::right << std::setw(alignment);
		}
		else if (alignment < 0)
		{
			ss << std::left << std::setw(-alignment);
		}
	}
	if (*endptr == ':')
	{
		fmt = endptr + 1;
	}

	args[index]->format(ss, fmt);
	return;
}


