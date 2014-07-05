#ifndef _CS_FORMAT_H
#define _CS_FORMAT_H

#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <sstream>

class CArgArray;
void _formatItem(std::ostringstream &ss, const std::string& item, const CArgArray& args);
void _formatTime(std::ostringstream &ss, time_t t);

class CArgBase
{
public:
	CArgBase() {}
	virtual ~CArgBase() {}
	virtual void format(std::ostringstream &ss, const std::string& fmt) = 0;
};

template <class T>
class CArg : public CArgBase
{
public:
	CArg(T arg) :_arg(arg) {}
	virtual ~CArg(){}
	virtual void format(std::ostringstream &ss, const std::string& fmt)
	{
		ss << _arg;
	}
private:
	T _arg;
};

//a example of extension
template <>
class CArg<time_t> : public CArgBase
{
public:
	CArg(time_t arg) : _arg(arg) {}
	virtual void format(std::ostringstream &ss, const std::string& fmt)
	{
		if (fmt[0] == 'T')
		{
			_formatTime(ss, _arg);
		}
		else
		{
			ss << _arg;
		}
	}
private:
	time_t _arg;
};

class CArgArray : public std::vector<CArgBase*>
{
public:
	CArgArray() {}
	~CArgArray()
	{
		std::for_each(begin(), end(), [](CArgBase* p){delete p; });
	}
};

template <class T>
static void transfer(CArgArray& argArray, T t)
{
	CArgBase* arg = new CArg<T>(t);
	argArray.push_back(arg);
}

template <class T, typename... Args>
static void transfer(CArgArray& argArray, T t, Args... args)
{
	transfer(argArray, t);
	transfer(argArray, args...);
}

template <typename... Args>
std::string CSFormat(const std::string& format, Args... args)
{
	if (sizeof...(args) == 0)
	{
		return format;
	}
	
	CArgArray argArray;
	transfer(argArray, args...);
	size_t start = 0;
	size_t pos = 0;
	std::ostringstream ss;
	while (true)
	{
		pos = format.find('{', start);
		ss << format.substr(start, pos - start);
		if (pos == std::string::npos)
		{	
			break;
		}
		if (format[pos + 1] == '{')
		{
			ss << '{';
			start = pos + 2;
			continue;
		}
		start = pos + 1;
		pos = format.find('}', start);
		if (pos == std::string::npos)
		{
			ss << format.substr(start-1);
			break;
		}

		_formatItem(ss, format.substr(start, pos - start), argArray);

		start = pos + 1;
	}
	
	return ss.str();
}

#endif
